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

#include "clock_init.h"
#include "pin_init.h"
#include "hal_uart.h"
#include "hal_exti.h"
#include "hal_syscfg.h"

/* KEY2. */
#define BOARD_KEY2_GPIO_PORT GPIOB
#define BOARD_KEY2_GPIO_PIN  GPIO_PIN_0

/* DEBUG UART. */
#define BOARD_DEBUG_UART_PORT        UART1
#define BOARD_DEBUG_UART_BAUDRATE    9600u
#define BOARD_DEBUG_UART_FREQ        CLOCK_APB2_FREQ

/*SYSCFG*/
#define BOARD_SYSCFG_EXTIPORT        SYSCFG_EXTIPort_GPIOD
#define BOARD_SYSCFG_EXTILINE        SYSCFG_EXTILine_7

/*EXTI*/
#define BOARD_EXTI_PORT              EXTI
#define BOARD_EXTI_LINE              EXTI_LINE_7
#define BOARD_EXTI_IRQN              EXTI9_5_IRQn
#define BOARD_EXTI_IRQHandler        EXTI9_5_IRQHandler
void BOARD_Init(void);

#endif /* __BOARD_INIT_H__ */
