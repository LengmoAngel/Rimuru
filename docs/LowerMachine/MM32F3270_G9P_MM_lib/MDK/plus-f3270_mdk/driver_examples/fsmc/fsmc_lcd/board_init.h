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

#define BOARD_LCD_BL_GPIO_PORT       GPIOG
#define BOARD_LCD_BL_GPIO_PIN        GPIO_PIN_6

#define BOARD_LCD_RST_GPIO_PORT      GPIOG
#define BOARD_LCD_RST_GPIO_PIN       GPIO_PIN_11

#define BOARD_LCD_FSMC_PORT          FSMC
#define BOARD_LCD_FSMC_SET_INDEX     0u
#define BOARD_LCD_FSMC_RS_BIT_INDEX  24u /* for RS line. left shift 1 bit when using 16-bit address mode. */

#define BOARD_LCD_WIDTH              (320u)
#define BOARD_LCD_HEIGHT             (480u)

void BOARD_Init(void);



#endif /* __BOARD_INIT_H__ */
