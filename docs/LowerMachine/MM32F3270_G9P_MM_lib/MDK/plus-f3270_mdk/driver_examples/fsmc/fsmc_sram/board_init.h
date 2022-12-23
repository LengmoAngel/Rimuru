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
#include "hal_fsmc.h"
#include "hal_gpio.h"

#include "clock_init.h"
#include "pin_init.h"

/* DEBUG UART. */
#define BOARD_DEBUG_UART_PORT        UART1
#define BOARD_DEBUG_UART_BAUDRATE    9600u
#define BOARD_DEBUG_UART_FREQ        CLOCK_APB2_FREQ

/* SRAM */
#define BOARD_SRAM_FSMC_PORT          FSMC
#define BOARD_SRAM_FSMC_SET_INDEX     0u
#define BOARD_SRAM_FSMC_BANK_INDEX    2u
#define BOARD_SRAM_FSMC_READ_PERIOD   0x63u
#define BOARD_SRAM_FSMC_ADDR_SET_TIME 0x3u
#define BOARD_SRAM_FSMC_WHITE_HOLD_TIME 0x3u
#define BOARD_SRAM_FSMC_WRITE_PERIOD  0x7u
#define BOARD_SRAM_FSMC_READY_SIGNAL  FSMC_ReadySignal_Internal
#define BOARD_SRAM_FSMC_SM_READ_PIPE  0u
#define BOARD_SRAM_FSMC_BUS_WIDTH     FSMC_BusWidth_16b

void BOARD_Init(void);



#endif /* __BOARD_INIT_H__ */
