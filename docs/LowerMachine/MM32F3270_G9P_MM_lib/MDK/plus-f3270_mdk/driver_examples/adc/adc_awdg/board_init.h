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

#include "clock_init.h"
#include "pin_init.h"


/* ADC. */
#define BOARD_ADC_PORT        ADC1
#define BOARD_ADC_IRQn        ADC1_ADC2_IRQn
#define BOARD_ADC_IRQHandler  ADC1_2_IRQHandler

#define BOARD_ADC_HW_COMP_CHN_NUM    1u   /* ADC1_VIN[1]. */
#define BOARD_ADC_HW_COMP_HIGH_LIMIT 3900u
#define BOARD_ADC_HW_COMP_LOW_LIMIT  3300

/* DEBUG UART. */
#define BOARD_DEBUG_UART_PORT        UART1
#define BOARD_DEBUG_UART_BAUDRATE    9600u
#define BOARD_DEBUG_UART_FREQ        CLOCK_APB2_FREQ

void BOARD_Init(void);
void BOARD_InitDebugConsole(void);

#endif /* __BOARD_INIT_H__ */
