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

#include "clock_init.h"
#include "pin_init.h"

/* LED0. */
#define BOARD_LED0_GPIO_PORT GPIOH
#define BOARD_LED0_GPIO_PIN  GPIO_PIN_2

/* LED1. */
#define BOARD_LED1_GPIO_PORT GPIOA
#define BOARD_LED1_GPIO_PIN  GPIO_PIN_15

/* LED2. */
#define BOARD_LED2_GPIO_PORT GPIOA
#define BOARD_LED2_GPIO_PIN  GPIO_PIN_0

/* LED3. */
#define BOARD_LED3_GPIO_PORT GPIOG
#define BOARD_LED3_GPIO_PIN  GPIO_PIN_13

/* KEY0. */
#define BOARD_KEY0_GPIO_PORT GPIOD
#define BOARD_KEY0_GPIO_PIN  GPIO_PIN_7 /* 对应板子上的K2 */

/* KEY1. */
#define BOARD_KEY1_GPIO_PORT GPIOG
#define BOARD_KEY1_GPIO_PIN  GPIO_PIN_7

/* KEY2. */
#define BOARD_KEY2_GPIO_PORT GPIOG
#define BOARD_KEY2_GPIO_PIN  GPIO_PIN_8

/* KEY3. */
#define BOARD_KEY3_GPIO_PORT GPIOG
#define BOARD_KEY3_GPIO_PIN  GPIO_PIN_9

/* DEBUG UART. */
#define BOARD_DEBUG_UART_PORT        UART1
#define BOARD_DEBUG_UART_BAUDRATE    9600u
#define BOARD_DEBUG_UART_FREQ        CLOCK_APB2_FREQ

void BOARD_Init(void);

#endif /* __BOARD_INIT_H__ */
