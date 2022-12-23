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

#include "clock_init.h"

/* LED0. */
#define BOARD_LED0_GPIO_PORT GPIOH
#define BOARD_LED0_GPIO_PIN  GPIO_PIN_2

/* DEBUG UART. */
#define BOARD_DEBUG_UART_PORT        UART1
#define BOARD_DEBUG_UART_BAUDRATE    9600u
#define BOARD_DEBUG_UART_FREQ        CLOCK_APB2_FREQ
#define BOARD_DEBUG_UART_IRQn        UART1_IRQn
#define BOARD_DEBUG_UART_IRQHandler  UART1_IRQHandler

void BOARD_Init(void);
void BOARD_LedOnTimeout(uint32_t ticks);

#endif /* __BOARD_INIT_H__ */
