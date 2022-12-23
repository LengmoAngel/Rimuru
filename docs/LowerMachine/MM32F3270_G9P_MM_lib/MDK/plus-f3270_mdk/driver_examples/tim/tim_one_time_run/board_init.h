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
#include "hal_gpio.h"
#include "hal_uart.h"
#include "hal_tim.h"

#include "clock_init.h"
#include "pin_init.h"

/* DEBUG UART. */
#define BOARD_DEBUG_UART_PORT        UART1
#define BOARD_DEBUG_UART_BAUDRATE    9600u
#define BOARD_DEBUG_UART_FREQ        CLOCK_APB2_FREQ

/* TIM1. */
#define BOARD_TIM_PORT              (TIM_Type *)TIM1
#define BOARD_TIM_IRQn              TIM1_UP_IRQn
#define BOARD_TIM_IRQHandler        TIM1_UP_IRQHandler
#define BOARD_TIM_FREQ              CLOCK_SYS_FREQ

void BOARD_Init(void);

#endif /* __BOARD_INIT_H__ */
