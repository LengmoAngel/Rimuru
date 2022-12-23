/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <stdio.h>

#include "board_init.h"

#include "hal_uart.h"

/*
 * Macros.
 */
#define APP_UART_TX_BUFF_LEN 8u


/*
 * Variables.
 */
volatile uint8_t  app_uart_tx_buff[APP_UART_TX_BUFF_LEN];
volatile uint32_t app_uart_tx_buff_idx = 0u;

/*
 * Declerations.
 */
void    app_uart_init(void);
uint8_t app_uart_getchar(void);
void    app_uart_putstr_int(uint8_t c);
void    app_uart_tx_isr_hook(void);

/*
 * Functions.
 */
int main(void)
{
    uint8_t ch;

    BOARD_Init();

    app_uart_init();

    while (1)
    {
        ch = app_uart_getchar();
        app_uart_putstr_int(ch);
    }
}

void app_uart_init(void)
{
    UART_Init_Type uart_init;

    /* Setup the xfer engine. */
    uart_init.ClockFreqHz   = BOARD_DEBUG_UART_FREQ; /* 48mhz, APB2. */
    uart_init.BaudRate      = BOARD_DEBUG_UART_BAUDRATE;
    uart_init.WordLength    = UART_WordLength_8b;
    uart_init.StopBits      = UART_StopBits_1;
    uart_init.Parity        = UART_Parity_None;
    uart_init.XferMode      = UART_XferMode_RxTx;
    uart_init.HwFlowControl = UART_HwFlowControl_None;
    UART_Init(BOARD_DEBUG_UART_PORT, &uart_init);

    /* Enable TX interrupt. */
    UART_ClearInterruptStatus(BOARD_DEBUG_UART_PORT, UART_INT_TX_EMPTY);
    NVIC_EnableIRQ(BOARD_DEBUG_UART_IRQn);

    /* Enable UART. */
    UART_Enable(BOARD_DEBUG_UART_PORT, true);
}

uint8_t app_uart_getchar(void)
{
    while ( 0u == (UART_STATUS_RX_DONE & UART_GetStatus(BOARD_DEBUG_UART_PORT)) )
    {}
    return UART_GetData(BOARD_DEBUG_UART_PORT);
}

void app_uart_putstr_int(uint8_t c)
{
    /* prepare the buffer. */
    for (uint32_t i = 0u; i < APP_UART_TX_BUFF_LEN; i++)
    {
        app_uart_tx_buff[i] = c;
    }
    app_uart_tx_buff_idx = 0u;

    /* enable the tx interrupt to transmit the buffer. */
    UART_EnableInterrupts(BOARD_DEBUG_UART_PORT, UART_INT_TX_EMPTY, true);
}

void app_uart_tx_isr_hook(void)
{
    if (   (0u != (UART_INT_TX_EMPTY & UART_GetEnabledInterrupts(BOARD_DEBUG_UART_PORT)))
        && (0u != (UART_INT_TX_EMPTY & UART_GetInterruptStatus(BOARD_DEBUG_UART_PORT)))  )
    {
        if (app_uart_tx_buff_idx == APP_UART_TX_BUFF_LEN)
        {
            /* UART_ClearInterruptStatus(UART1, UART_INT_TX_EMPTY); */
            UART_EnableInterrupts(BOARD_DEBUG_UART_PORT, UART_INT_TX_EMPTY, false);
        }
        else
        {
            UART_PutData(BOARD_DEBUG_UART_PORT, app_uart_tx_buff[app_uart_tx_buff_idx]);
            app_uart_tx_buff_idx++;
        }
    }
}

/* UARTx ISR entry. */
void BOARD_DEBUG_UART_IRQHandler(void)
{
    app_uart_tx_isr_hook();
}

/* EOF. */
