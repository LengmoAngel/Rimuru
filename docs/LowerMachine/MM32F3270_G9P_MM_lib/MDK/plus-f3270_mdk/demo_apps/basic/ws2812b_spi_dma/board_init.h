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
#include "hal_spi.h"
#include "hal_dma.h"
#include "hal_dma_request.h"

#include "clock_init.h"
#include "pin_init.h"

/* DEBUG UART. */
#define BOARD_DEBUG_UART_PORT        UART1
#define BOARD_DEBUG_UART_BAUDRATE    9600u
#define BOARD_DEBUG_UART_FREQ        CLOCK_APB2_FREQ

void BOARD_Init(void);

#define WS2812B_LIST_LED_NUM  8u

#define WS2812B_COLOR_GREEN   0xFF0000
#define WS2812B_COLOR_RED     0xFF00
#define WS2812B_COLOR_BLUE    0xFF

void ws2812b_init(void);
void ws2812b_display_set_color(uint32_t color, uint32_t index);
void ws2812b_display_clear_color(void);
void ws2812b_display_buff_update_all(void);
void ws2812b_display_start(void);
void ws2812b_display_waitdone(void);

#endif /* __BOARD_INIT_H__ */
