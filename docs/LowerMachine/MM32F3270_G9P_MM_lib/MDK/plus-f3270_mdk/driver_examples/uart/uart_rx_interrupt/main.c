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
#define APP_UART_RX_BUFF_LEN 8u


/*
 * Variables.
 */
volatile uint8_t  app_uart_rx_buff[APP_UART_RX_BUFF_LEN];
volatile uint32_t app_uart_rx_buff_idx = 0u;

/*
 * Declerations.
 */
void app_uart_init(void);
void app_uart_rx_isr_hook(void);


/*
 * Functions.
 */
int main(void)
{
    BOARD_Init();

    app_uart_init();

    while (1)
    {
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

    /* Enable RX interrupt. */
    UART_EnableInterrupts(BOARD_DEBUG_UART_PORT, UART_INT_RX_DONE, true);
    NVIC_EnableIRQ(BOARD_DEBUG_UART_IRQn);

    /* Enable UART. */
    UART_Enable(BOARD_DEBUG_UART_PORT, true);
}

void app_uart_rx_isr_hook(void)
{
    if (   (0u != (UART_INT_RX_DONE & UART_GetEnabledInterrupts(BOARD_DEBUG_UART_PORT)))
        && (0u != (UART_INT_RX_DONE & UART_GetInterruptStatus(BOARD_DEBUG_UART_PORT))) )
    {
        app_uart_rx_buff[app_uart_rx_buff_idx] = UART_GetData(BOARD_DEBUG_UART_PORT); /* read data to clear rx interrupt bits. */
        BOARD_LedOnTimeout(app_uart_rx_buff[app_uart_rx_buff_idx] % 4u + 1u);
        app_uart_rx_buff_idx = (app_uart_rx_buff_idx+1)%APP_UART_RX_BUFF_LEN;
    }
}

/* BOARD_DEBUG_UART_IRQHandler ISR entry. */
void BOARD_DEBUG_UART_IRQHandler(void)
{
    app_uart_rx_isr_hook();
}

/* EOF. */
