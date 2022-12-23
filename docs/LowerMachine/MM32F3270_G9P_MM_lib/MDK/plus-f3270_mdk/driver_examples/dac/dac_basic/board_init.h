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
#include "hal_dac.h"
#include "clock_init.h"
#include "pin_init.h"
#include "hal_uart.h"

/* DEBUG UART. */
#define BOARD_DEBUG_UART_PORT             UART1
#define BOARD_DEBUG_UART_BAUDRATE         9600u
#define BOARD_DEBUG_UART_FREQ             CLOCK_APB2_FREQ

/* DAC. */
#define BOARD_DAC_PORT     DAC
#define BOARD_DAC_CHANNEL  DAC_CHN_2

void BOARD_Init(void);

#endif /* __BOARD_INIT_H__ */
