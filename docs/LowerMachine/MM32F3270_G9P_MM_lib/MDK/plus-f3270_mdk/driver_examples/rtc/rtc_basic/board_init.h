/*
 * Copyright 2022 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __BOARD_INIT_H__
#define __BOARD_INIT_H__

#include <stdio.h>

#include "hal_common.h"
#include "hal_rcc.h"
#include "hal_gpio.h"
#include "hal_uart.h"
#include "hal_i2c.h"
#include "hal_rtc.h"

#include "clock_init.h"
#include "pin_init.h"

/* LED0. */
#define BOARD_LED0_GPIO_PORT GPIOA
#define BOARD_LED0_GPIO_PIN  GPIO_Pin_15

/* LED1. */
#define BOARD_LED1_GPIO_PORT GPIOB
#define BOARD_LED1_GPIO_PIN  GPIO_Pin_3

/* LED2. */
#define BOARD_LED2_GPIO_PORT GPIOB
#define BOARD_LED2_GPIO_PIN  GPIO_Pin_4

/* LED3. */
#define BOARD_LED3_GPIO_PORT GPIOB
#define BOARD_LED3_GPIO_PIN  GPIO_Pin_5

/* KEY0. */
#define BOARD_KEY0_GPIO_PORT GPIOB
#define BOARD_KEY0_GPIO_PIN  GPIO_Pin_2 /* 对应板子上的K2 */

/* KEY1. */
#define BOARD_KEY1_GPIO_PORT GPIOB
#define BOARD_KEY1_GPIO_PIN  GPIO_Pin_10

/* KEY2. */
#define BOARD_KEY2_GPIO_PORT GPIOB
#define BOARD_KEY2_GPIO_PIN  GPIO_Pin_0

/* KEY3. */
#define BOARD_KEY3_GPIO_PORT GPIOB
#define BOARD_KEY3_GPIO_PIN  GPIO_Pin_1 /* 注意，MB-036板子上的K1是反逻辑 */

/* DEBUG UART. */
#define BOARD_DEBUG_UART_PORT        UART1
#define BOARD_DEBUG_UART_BAUDRATE    9600u
#define BOARD_DEBUG_UART_FREQ        CLOCK_APB2_FREQ

/* DEBUG I2C. */
#define BOARD_I2C_PORT               I2C1
#define BOARD_I2C_IRQn               I2C1_IRQn
#define BOARD_I2C_IRQ_HANDLER_FUNC   I2C1_IRQHandler

/* RTC */
#define BOARD_RTC_PORT               RTC
#define BOARD_RTC_IRQn               RTC_IRQn
#define BOARD_RTC_IRQ_HANDLER_FUNC   RTC_IRQHandler



void BOARD_Init(void);

#endif /* __BOARD_INIT_H__ */

