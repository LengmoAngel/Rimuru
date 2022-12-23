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
#include "hal_gpio.h"

#include "clock_init.h"
#include "pin_init.h"

/* DEBUG UART. */
#define BOARD_DEBUG_UART_PORT        UART1
#define BOARD_DEBUG_UART_BAUDRATE    9600u
#define BOARD_DEBUG_UART_FREQ        CLOCK_APB2_FREQ

/* SPI3. */
#define BOARD_FLASH_SPI_PORT          SPI2
#define BOARD_FLASH_SPI_BAUDRATE      400000u /* 400khz. */
#define BOARD_FLASH_SPI_FREQ          CLOCK_APB1_FREQ

#define BOARD_FLASH_CS_GPIO_PORT      GPIOE
#define BOARD_FLASH_CS_GPIO_PIN       GPIO_PIN_3

void BOARD_Init(void);

#endif /* __BOARD_INIT_H__ */
