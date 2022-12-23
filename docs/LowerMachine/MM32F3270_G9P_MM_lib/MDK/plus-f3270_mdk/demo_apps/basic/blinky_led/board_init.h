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

#include "clock_init.h"

/* DEBUG UART. */
#define BOARD_DEBUG_UART_PORT        UART1
#define BOARD_DEBUG_UART_BAUDRATE    9600u
#define BOARD_DEBUG_UART_FREQ        CLOCK_APB2_FREQ

/* LED. */
#define BOARD_LED0_GPIO_PORT         GPIOH
#define BOARD_LED0_GPIO_PIN          GPIO_PIN_2

#define BOARD_LED1_GPIO_PORT         GPIOA
#define BOARD_LED1_GPIO_PIN          GPIO_PIN_15

#define BOARD_LED2_GPIO_PORT         GPIOA
#define BOARD_LED2_GPIO_PIN          GPIO_PIN_0

#define BOARD_LED3_GPIO_PORT         GPIOG
#define BOARD_LED3_GPIO_PIN          GPIO_PIN_13

void BOARD_Init(void);

void leds_init(void);
void leds_on(void);
void leds_off(void);

#endif /* __BOARD_INIT_H__ */
