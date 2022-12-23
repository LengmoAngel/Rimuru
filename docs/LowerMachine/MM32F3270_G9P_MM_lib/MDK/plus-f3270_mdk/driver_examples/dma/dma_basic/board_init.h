/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __BOARD_INIT_H__
#define __BOARD_INIT_H__

#include <stdio.h>
#include <stdint.h>

#include "hal_common.h"
#include "hal_uart.h"
#include "hal_dma.h"

#include "clock_init.h"
#include "pin_init.h"


/* DEBUG UART. */
#define BOARD_DEBUG_UART_PORT        UART1
#define BOARD_DEBUG_UART_BAUDRATE    9600u
#define BOARD_DEBUG_UART_FREQ        CLOCK_APB2_FREQ
#define BOARD_DEBUG_UART_IRQn        UART1_IRQn
#define BOARD_DEBUG_UART_IRQHandler  UART1_IRQHandler

/* DMA. */
#define BOARD_DMA_PORT        DMA1
#define BOARD_DMA_CHANNEL     0u

void BOARD_Init(void);

#endif /* __BOARD_INIT_H__ */
