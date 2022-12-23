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
#include "hal_adc.h"
#include "hal_dma_request.h"
#include "hal_dma.h"

#include "clock_init.h"
#include "pin_init.h"

/* ADC. */
#define BOARD_ADC_PORT        ADC1
/* DEBUG UART. */
#define BOARD_DEBUG_UART_PORT        UART1
#define BOARD_DEBUG_UART_BAUDRATE    9600u
#define BOARD_DEBUG_UART_FREQ        CLOCK_APB2_FREQ
/* DMA for ADC  */
#define BOARD_DMA_ADC_PORT        DMA1
#define BOARD_DMA_ADC_CHN         DMA_REQ_DMA1_ADC1
#define BOARD_DMA_ADC_IRQn        DMA1_CH1_IRQn
#define BOARD_DMA_ADC_IRQHandler  DMA1_CH1_IRQHandler

/* ch1 and ch2 can be different for more sensors. */
#define BOARD_ADC_CHN_NUM_1       10u
#define BOARD_ADC_CHN_NUM_2       10u

void BOARD_Init(void);
void BOARD_InitDebugConsole(void);

#endif /* __BOARD_INIT_H__ */
