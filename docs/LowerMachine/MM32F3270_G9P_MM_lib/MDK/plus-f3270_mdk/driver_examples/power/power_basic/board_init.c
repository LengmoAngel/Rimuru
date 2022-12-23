/*
 * Copyright 2022 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include "board_init.h"
#include "hal_gpio.h"

/*
* Definitions.
*/

/*
 * Variables.
 */
/* Configure sleep mode parameters. */
static POWER_SleepConf_Type sleep_conf =
{
    .SleepOnExit = false,
    .WakeUpMode = POWER_WakeUp_Interrupt,
};

/* Configure stop mode parameters. */
static POWER_StopConf_Type stop_conf =
{
    .DeepStop = false,
    .WakeUpMode = POWER_WakeUp_Interrupt,
};

/* Configure deep stop mode parameters. */
static POWER_StopConf_Type deep_stop_conf =
{
    .DeepStop = true,
    .WakeUpMode = POWER_WakeUp_Interrupt,
};

/* Configure standby mode wake up pin parameters. */
static PWR_StandbyWakeUpPinConf_Type WakeUpPinConf =
{
    .Pins = BOARD_POWER_STANDBYWAKEUP_PORT,
    .TrgIn = PWR_StandbyWakeUpPinTriggerIn_FallingEdge,
};

/* Configure standby mode parameters. */
static POWER_StandbyConf_Type standby_conf =
{
    .Delay = BOARD_POWER_STANDBYWAKEUP_DELAY,
    .WakeUpMode = POWER_WakeUp_Interrupt,
};

/*
* Declerations.
*/
void BOARD_InitDebugConsole(void);

/*
* Functions.
*/
void BOARD_Init(void)
{
    BOARD_InitBootClocks();
    BOARD_InitPins();

    BOARD_InitDebugConsole();
}

void BOARD_InitDebugConsole(void)
{
    UART_Init_Type uart_init;

    uart_init.ClockFreqHz   = BOARD_DEBUG_UART_FREQ;
    uart_init.BaudRate      = BOARD_DEBUG_UART_BAUDRATE;
    uart_init.WordLength    = UART_WordLength_8b;
    uart_init.StopBits      = UART_StopBits_1;
    uart_init.Parity        = UART_Parity_None;
    uart_init.XferMode      = UART_XferMode_RxTx;
    uart_init.HwFlowControl = UART_HwFlowControl_None;
    UART_Init(BOARD_DEBUG_UART_PORT, &uart_init);
    UART_Enable(BOARD_DEBUG_UART_PORT, true);
}

void BOARD_ResetDebugConsole(uint32_t ClockFreq)
{
    UART_Init_Type uart_init;
    
    uart_init.ClockFreqHz   = ClockFreq; /* 2mhz, APB2. */
    uart_init.BaudRate      = BOARD_DEBUG_UART_BAUDRATE;
    uart_init.WordLength    = UART_WordLength_8b;
    uart_init.StopBits      = UART_StopBits_1;
    uart_init.Parity        = UART_Parity_None;
    uart_init.XferMode      = UART_XferMode_RxTx;
    uart_init.HwFlowControl = UART_HwFlowControl_None;
    UART_Init(BOARD_DEBUG_UART_PORT, &uart_init);
    UART_Enable(BOARD_DEBUG_UART_PORT, true);
}

void BOARD_PowerModeSelect(uint8_t ch)
{
    switch (ch)
    {
        case 'a':
            CLOCK_ResetToDefault();
            BOARD_ResetDebugConsole(BOARD_DEBUG_UART_FREQ);
            printf("\r\nMCU is going in run mode...\r\n");
            POWER_SelectMode(POWER_Mode_Run, NULL);
            break;
        case 'b':
            CLOCK_SetClock_2M();
            BOARD_ResetDebugConsole(BOARD_DEBUG_UART_FREQ_2M);
            printf("\r\nMCU is going in low power run mode...\r\n");
            POWER_SelectMode(POWER_Mode_LowPowerRun, NULL);
            break;
        case 'c':
            printf("\r\nMCU is going in sleep mode...\r\n");
            POWER_SelectMode(POWER_Mode_Sleep, &sleep_conf);
            break;
        case 'd':
            CLOCK_SetClock_2M();
            BOARD_ResetDebugConsole(BOARD_DEBUG_UART_FREQ_2M);
            printf("\r\nMCU is going in low power sleep mode...\r\n");
            POWER_SelectMode(POWER_Mode_LowPowerSleep, &sleep_conf);
            break;
        case 'e':
            printf("\r\nMCU is going in stop mode...\r\n");
            POWER_SelectMode(POWER_Mode_Stop, &stop_conf);
            break;
        case 'f':
            printf("\r\nMCU is going in deep stop mode...\r\n");
            POWER_SelectMode(POWER_Mode_DeepStop, &deep_stop_conf);
            break;
        case 'g':
            printf("\r\nMCU is going in standby mode...\r\n");
            POWER_EnableStandbyWakeUpPin(&WakeUpPinConf);
            POWER_SelectMode(POWER_Mode_Standby, &standby_conf);
            break;
        default:
            break;
    }
}

#if defined(__ARMCC_VERSION)
int fputc(int c, FILE *f)
{
    (void)(f);
    while ( 0u == (UART_STATUS_TX_EMPTY & UART_GetStatus(BOARD_DEBUG_UART_PORT)) )
    {}
    UART_PutData(BOARD_DEBUG_UART_PORT, (uint8_t)(c));
    return c;
}

int fgetc(FILE *f)
{
    (void)(f);
    while ( 0u == (UART_STATUS_RX_DONE & UART_GetStatus(BOARD_DEBUG_UART_PORT)) )
    {}
    return UART_GetData(BOARD_DEBUG_UART_PORT);
}

#elif defined(__GNUC__)

/*
 * Called by libc stdio fwrite functions
 */
int _write(int fd, char *ptr, int len)
{
    int i = 0;

    /*
     * write "len" of char from "ptr" to file id "fd"
     * Return number of char written.
     *
    * Only work for STDOUT, STDIN, and STDERR
     */
    if (fd > 2)
    {
        return -1;
    }

    while (*ptr && (i < len))
    {
        while ( 0u == (UART_STATUS_TX_EMPTY & UART_GetStatus(BOARD_DEBUG_UART_PORT)) )
        {}
        UART_PutData(BOARD_DEBUG_UART_PORT, (uint8_t)(*ptr));
        i++;
        ptr++;
    }

    return i;
}

/*
 * Called by the libc stdio fread fucntions
 *
 * Implements a buffered read with line editing.
 */
int _read(int fd, char *ptr, int len)
{
    int my_len;

    if (fd > 2)
    {
        return -1;
    }

    my_len = 0;
    while (len > 0)
    {
        while ( 0u == (UART_STATUS_RX_DONE & UART_GetStatus(BOARD_DEBUG_UART_PORT)) )
        {}
        *ptr = UART_GetData(BOARD_DEBUG_UART_PORT);
        len--;
        my_len++;

        if ( (*ptr == '\r') || (*ptr == '\n') || (*ptr == '\0') )
        {
            break;
        }

        ptr++;
    }

    return my_len; /* return the length we got */
}


int putchar(int c)
{
    while ( 0u == (UART_STATUS_TX_EMPTY & UART_GetStatus(BOARD_DEBUG_UART_PORT)) )
    {}
    UART_PutData(BOARD_DEBUG_UART_PORT, (uint8_t)(c));
    return c;
}

int getchar(void)
{
    while ( 0u == (UART_STATUS_RX_DONE & UART_GetStatus(BOARD_DEBUG_UART_PORT)) )
    {}
    return UART_GetData(BOARD_DEBUG_UART_PORT);
}

#elif (defined(__ICCARM__))
/*
 * Called by libc stdio fwrite functions
 */
int __write(int fd, char *ptr, int len)
{
    int i = 0;

    /*
     * write "len" of char from "ptr" to file id "fd"
     * Return number of char written.
     *
    * Only work for STDOUT, STDIN, and STDERR
     */
    if (fd > 2)
    {
        return -1;
    }

    while (*ptr && (i < len))
    {
        while ( 0u == (UART_STATUS_TX_EMPTY & UART_GetStatus(BOARD_DEBUG_UART_PORT)) )
        {}
        UART_PutData(BOARD_DEBUG_UART_PORT, (uint8_t)(*ptr));
        i++;
        ptr++;
    }

    return i;
}

/*
 * Called by the libc stdio fread fucntions
 *
 * Implements a buffered read with line editing.
 */
int __read(int fd, char *ptr, int len)
{
    int my_len;

    if (fd > 2)
    {
        return -1;
    }

    my_len = 0;
    while (len > 0)
    {
        while ( 0u == (UART_STATUS_RX_DONE & UART_GetStatus(BOARD_DEBUG_UART_PORT)) )
        {}
        *ptr = UART_GetData(BOARD_DEBUG_UART_PORT);
        len--;
        my_len++;

        if ( (*ptr == '\r') || (*ptr == '\n') || (*ptr == '\0') )
        {
            break;
        }

        ptr++;
    }

    return my_len; /* return the length we got */
}
/* These function __write and __read is used to support IAR toolchain to printf and scanf. */

int fputc(int ch, FILE *f)
{
    while ( 0u == (UART_STATUS_TX_EMPTY & UART_GetStatus(BOARD_DEBUG_UART_PORT)) )
    {}
    UART_PutData(BOARD_DEBUG_UART_PORT, (uint8_t)(ch));
    return ch;
}

int fgetc(FILE *f)
{
    while ( 0u == (UART_STATUS_RX_DONE & UART_GetStatus(BOARD_DEBUG_UART_PORT)) )
    {}
    return UART_GetData(BOARD_DEBUG_UART_PORT);
}

#endif

/* EOF. */
