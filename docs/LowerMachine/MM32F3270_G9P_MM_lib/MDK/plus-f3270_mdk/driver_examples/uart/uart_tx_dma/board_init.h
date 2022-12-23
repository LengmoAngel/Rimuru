/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __BOARD_INIT_H__
#define __BOARD_INIT_H__

#include <stdio.h>

#include "hal_common.h"
#include "hal_dma.h"

#include "clock_init.h"

#define BOARD_LED0_GPIO_PORT GPIOH
#define BOARD_LED0_GPIO_PIN  GPIO_PIN_2

/* DEBUG UART. */
#define BOARD_DEBUG_UART_PORT         UART1
#define BOARD_DEBUG_UART_BAUDRATE     9600u
#define BOARD_DEBUG_UART_FREQ         CLOCK_APB2_FREQ

/* DMA for UART1 Tx. */
#define BOARD_DMA_UART_TX_PORT        DMA1
#define BOARD_DMA_UART_TX_CHANNEL     DMA_REQ_DMA1_UART1_TX
#define BOARD_DMA_UART_TX_IRQn        DMA1_CH4_IRQn
#define BOARD_DMA_UART_TX_IRQHandler  DMA1_CH4_IRQHandler

void BOARD_Init(void);
void BOARD_LedOnTimeout(uint32_t ticks);

#endif /* __BOARD_INIT_H__ */
