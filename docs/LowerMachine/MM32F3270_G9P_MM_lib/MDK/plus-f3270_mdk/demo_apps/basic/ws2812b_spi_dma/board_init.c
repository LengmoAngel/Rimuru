/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board_init.h"

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

//#define WS2812B_LIST_LED_NUM   8u
#define WS2812B_DISP_PIXEL_LEN 24u /* 24bit.  */
#define WS2812B_DISP_BUFF_LEN  (WS2812B_DISP_PIXEL_LEN * WS2812B_LIST_LED_NUM)

volatile uint8_t ws2812b_disp_bit_buff[WS2812B_DISP_BUFF_LEN]; /* bit stream of colors, to be transferred by hardware. */
volatile uint8_t ws2812b_disp_byte_buff[WS2812B_LIST_LED_NUM * 3u]; /* byte stream of colors, to represent the colors. */
volatile bool ws2812b_spi_tx_dma_done = true;

#define WS2812B_SPI_TX_PORT            SPI3
#define WS2812B_SPI_TX_FREQ            CLOCK_APB1_FREQ
#define WS2812B_SPI_TX_BAUDRATE        6400000u  /* 6.4Mbps */

#define WS2812B_SPI_TX_DMA_PORT        DMA2
#define WS2812B_SPI_TX_DMA_CHANNEL     DMA_REQ_DMA2_SPI3_TX
#define WS2812B_SPI_TX_DMA_IRQ         DMA2_CH2_IRQn
#define WS2812B_SPI_TX_DMA_IRQHandler  DMA2_CH2_IRQHandler

#define WS2812B_BIT0_CODE              0xC0
#define WS2812B_BIT1_CODE              0xF0

void ws2812b_init(void)
{
    /* pins are ready in pin_init.c */

    /* dma. */
    DMA_Channel_Init_Type dma_channel_init;
    dma_channel_init.XferMode = DMA_XferMode_MemoryToPeriph;
    dma_channel_init.ReloadMode = DMA_ReloadMode_AutoReload; /* DMA_AutoReloadMode_Circular */
    dma_channel_init.PeriphAddrIncMode = DMA_AddrIncMode_StayAfterXfer;
    dma_channel_init.MemAddrIncMode = DMA_AddrIncMode_IncAfterXfer;
    dma_channel_init.XferWidth = DMA_XferWidth_8b;
    dma_channel_init.Priority = DMA_Priority_Low;
    dma_channel_init.XferCount = WS2812B_DISP_BUFF_LEN;
    dma_channel_init.MemAddr = (uint32_t)ws2812b_disp_bit_buff;
    dma_channel_init.PeriphAddr = SPI_GetTxDataRegAddr(WS2812B_SPI_TX_PORT); /* use tx data register here. */
    DMA_InitChannel(WS2812B_SPI_TX_DMA_PORT, WS2812B_SPI_TX_DMA_CHANNEL, &dma_channel_init);

    /* enable interrupt for DMA. */
    NVIC_EnableIRQ(WS2812B_SPI_TX_DMA_IRQ);
    DMA_EnableChannelInterrupts(WS2812B_SPI_TX_DMA_PORT, WS2812B_SPI_TX_DMA_CHANNEL, DMA_CHN_INT_XFER_DONE, true);

    /* spi3. */
    SPI_Master_Init_Type spi_init;
    spi_init.ClockFreqHz = WS2812B_SPI_TX_FREQ;
    spi_init.BaudRate = WS2812B_SPI_TX_BAUDRATE;
    spi_init.XferMode = SPI_XferMode_TxRx;
    spi_init.PolPha = SPI_PolPha_Alt0;
    spi_init.DataWidth = SPI_DataWidth_8b;
    spi_init.LSB = false;
    spi_init.AutoCS = true;
    SPI_InitMaster(WS2812B_SPI_TX_PORT, &spi_init);
    SPI_EnableDMA(WS2812B_SPI_TX_PORT, true); /* Events would trigger the DMA instead of interrupt. */
    SPI_Enable(WS2812B_SPI_TX_PORT, true);

    /* clear the led matrix buff. */
    uint8_t *p_buff = (uint8_t *)ws2812b_disp_bit_buff;
    for (uint32_t i = 0u; i < WS2812B_DISP_PIXEL_LEN * WS2812B_LIST_LED_NUM; i++, p_buff++)
    {
        *p_buff = WS2812B_BIT0_CODE;
    }

    ws2812b_spi_tx_dma_done = true;
}

/* from led_disp_byte_buff to led_disp_bit_buff */
void ws2812b_display_buff_update_all(void)
{
    uint8_t *p_buff1 = (uint8_t *)ws2812b_disp_byte_buff;
    uint8_t *p_buff2 = (uint8_t *)ws2812b_disp_bit_buff;

    for (uint32_t i1 = 0u; i1 < 3u * WS2812B_LIST_LED_NUM; i1++, p_buff1++)
    {
        for (uint32_t i2 = 0u; i2 < 8u; i2++, p_buff2++)
        {
            if ( 0u == (*p_buff1 & (1u << (7u - i2))) )
            {
                *p_buff2 = WS2812B_BIT0_CODE;
            }
            else
            {
                *p_buff2 = WS2812B_BIT1_CODE;
            }
        }
    }
}

void ws2812b_display_set_color(uint32_t color, uint32_t index)
{
    uint8_t *p_buff = (uint8_t *)ws2812b_disp_byte_buff + index * 3u;

    /* mark the brightness of each leds. */
    *p_buff++  = (uint8_t)((color & 0xFF0000) >> 16u);
    *p_buff++  = (uint8_t)((color & 0x00FF00) >> 8u );
    *p_buff    = (uint8_t)((color & 0x0000FF)       );

    /* update to the bit buff. */
    //ws2812b_display_buff_update_all();
}

void ws2812b_display_clear_color(void)
{
    for (uint32_t i = 0u; i < WS2812B_LIST_LED_NUM; i++)
    {
        ws2812b_display_set_color(0u, i);
    }
}

/* ISP for SPI_TX DMA done. */
void WS2812B_SPI_TX_DMA_IRQHandler(void)
{
    if (0u != (DMA_CHN_INT_XFER_DONE & DMA_GetChannelInterruptStatus(WS2812B_SPI_TX_DMA_PORT, WS2812B_SPI_TX_DMA_CHANNEL)) )
    {
        ws2812b_spi_tx_dma_done = true;
        DMA_ClearChannelInterruptStatus(WS2812B_SPI_TX_DMA_PORT, WS2812B_SPI_TX_DMA_CHANNEL, DMA_CHN_INT_XFER_DONE);

        /* The DMA channel would be disbaled automatically when the xfer is done. */
        //DMA_EnableChannel(BOARD_DMA_UART_TX_PORT, BOARD_DMA_UART_TX_CHANNEL, true); /* Enable the DMA channel for the next xfer. */
    }
}

void ws2812b_display_start(void)
{
    ws2812b_display_waitdone();
    ws2812b_spi_tx_dma_done = false;
    DMA_EnableChannel(WS2812B_SPI_TX_DMA_PORT, WS2812B_SPI_TX_DMA_CHANNEL, true);
}

void ws2812b_display_waitdone(void)
{
    while (!ws2812b_spi_tx_dma_done) /* wait while the dma is busy. */
    {}
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
