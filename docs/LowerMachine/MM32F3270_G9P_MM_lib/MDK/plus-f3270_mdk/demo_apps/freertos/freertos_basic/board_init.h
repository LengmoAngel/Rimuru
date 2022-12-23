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
#include "hal_rcc.h"
#include "hal_uart.h"

#include "clock_init.h"
#include "pin_init.h"

/* DEBUG UART. */
#define BOARD_DEBUG_UART_PORT        UART1
#define BOARD_DEBUG_UART_BAUDRATE    9600u
#define BOARD_DEBUG_UART_FREQ        CLOCK_APB2_FREQ

/* LED. */
#define BOARD_LED0_GPIO_PORT         GPIOH
#define BOARD_LED0_GPIO_PIN          GPIO_PIN_2

#define BOARD_LED1_GPIO_PORT         GPIOA
#define BOARD_LED1_GPIO_PIN          GPIO_PIN_15

void BOARD_Init(void);
void led0_onoff(bool onoff);
void led1_onoff(bool onoff);

#endif /* __BOARD_INIT_H__ */
