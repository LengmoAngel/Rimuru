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

/* TIM2. */
#define BOARD_TIM_PORT              (TIM_Type *)TIM8
#define BOARD_TIM_IRQn              TIM8_UP_IRQn
#define BOARD_TIM_IRQHandler        TIM8_UP_IRQHandler
#define BOARD_TIM_FREQ              CLOCK_SYS_FREQ
#define BOARD_TIM_CHN_1             TIM_CHN_1
#define BOARD_TIM_CHN_2             TIM_CHN_2
#define BOARD_TIM_STATUS_CHN_EVENT  TIM_STATUS_CHN1_EVENT
#define BOARD_TIM_CHN_1_PIN         GPIO_PIN_2
#define BOARD_TIM_CHN_2_PIN         GPIO_PIN_10
#define BOARD_TIM_CHN_PORT          GPIOB

void BOARD_Init(void);

#endif /* __BOARD_INIT_H__ */
