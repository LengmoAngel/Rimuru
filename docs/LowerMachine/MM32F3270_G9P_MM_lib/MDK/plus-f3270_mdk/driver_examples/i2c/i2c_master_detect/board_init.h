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
#include "hal_rcc.h"
#include "hal_gpio.h"
#include "hal_uart.h"
#include "hal_i2c.h"

#include "clock_init.h"
#include "pin_init.h"

/* I2C. */
#define BOARD_I2C_PORT               I2C1
#define BOARD_I2C_IRQn               I2C1_IRQn
#define BOARD_I2C_IRQHandler         I2C1_IRQHandler
#define BOARD_I2C_FREQ               CLOCK_APB1_FREQ


/* DEBUG UART. */
#define BOARD_DEBUG_UART_PORT        UART1
#define BOARD_DEBUG_UART_BAUDRATE    9600u
#define BOARD_DEBUG_UART_FREQ        CLOCK_APB2_FREQ


void BOARD_Init(void);

#endif /* __BOARD_INIT_H__ */
