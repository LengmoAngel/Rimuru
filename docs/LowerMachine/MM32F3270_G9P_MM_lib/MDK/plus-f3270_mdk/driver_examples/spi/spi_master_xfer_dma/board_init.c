/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board_init.h"
#include "clock_init.h"
#include "pin_init.h"

#include "hal_rcc.h"
#include "hal_uart.h"

/*
* Definitions.
*/

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
    /* UART1. */
    RCC_EnableAPB2Periphs(RCC_APB2_PERIPH_UART1, true);
    RCC_ResetAPB2Periphs(RCC_APB2_PERIPH_UART1);

    UART_Init_Type uart_init;

    uart_init.ClockFreqHz   = BOARD_DEBUG_UART_FREQ; /* 48mhz, APB2. */
    uart_init.BaudRate      = BOARD_DEBUG_UART_BAUDRATE;
    uart_init.WordLength    = UART_WordLength_8b;
    uart_init.StopBits      = UART_StopBits_1;
    uart_init.Parity        = UART_Parity_None;
    uart_init.XferMode      = UART_XferMode_RxTx;
    uart_init.HwFlowControl = UART_HwFlowControl_None;
    UART_Init(BOARD_DEBUG_UART_PORT, &uart_init);
    UART_Enable(BOARD_DEBUG_UART_PORT, true);
}

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

/* EOF. */
