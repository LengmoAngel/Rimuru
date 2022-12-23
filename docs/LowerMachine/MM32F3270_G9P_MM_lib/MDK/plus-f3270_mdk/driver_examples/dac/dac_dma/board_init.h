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
#include "hal_dma_request.h"
#include "hal_dma.h"
#include "hal_uart.h"

/* DEBUG UART. */
#define BOARD_DEBUG_UART_PORT             UART1
#define BOARD_DEBUG_UART_BAUDRATE         9600u
#define BOARD_DEBUG_UART_FREQ             CLOCK_APB2_FREQ

/* DAC. */
#define BOARD_DAC_PORT                    DAC
#define BOARD_DAC_CHANNEL                 DAC_CHN_1
#define BOARD_DMA_DAC_PORT                DMA2
#define BOARD_DMA_DAC_CHANNEL             DMA_REQ_DMA2_DAC_CH1
#define BOARD_DMA_DAC_IRQn                DMA2_CH3_IRQn
#define BOARD_DMA_DAC_IRQHandler          DMA2_CH3_IRQHandler
#define BOARD_DAC_TRGSOURCE               DAC_TrgSource_Alt7 /* software trigger. */

void BOARD_Init(void);

#endif /* __BOARD_INIT_H__ */
