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
#include "hal_adc.h"
#include "hal_uart.h"
#include "hal_rcc.h"
#include "hal_comp.h"

#include "clock_init.h"
#include "pin_init.h"


/* COMP. */
#define BOARD_COMP_PORT        COMP
#define BOARD_COMP_CHN_NUM     0u
#define BOARD_COMP_OUT         COMP_OutMux_Alt0 /* No output. */
#define BOARD_COMP_POS_IN      COMP_InMux_Alt0 /* PA0. */
#define BOARD_COMP_INV_IN      COMP_InMux_Alt0 /* PA4. */

/* DEBUG UART. */
#define BOARD_DEBUG_UART_PORT        UART1
#define BOARD_DEBUG_UART_BAUDRATE    9600u
#define BOARD_DEBUG_UART_FREQ        CLOCK_APB2_FREQ


void BOARD_Init(void);
void BOARD_InitDebugConsole(void);

#endif /* __BOARD_INIT_H__ */
