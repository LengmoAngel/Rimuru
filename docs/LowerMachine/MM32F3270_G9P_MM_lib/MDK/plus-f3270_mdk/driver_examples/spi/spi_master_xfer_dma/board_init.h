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
#include "clock_init.h"
#include "pin_init.h"
#include "hal_dma_request.h"

/* DEBUG UART. */
#define BOARD_DEBUG_UART_PORT        UART1
#define BOARD_DEBUG_UART_BAUDRATE    9600u
#define BOARD_DEBUG_UART_FREQ        CLOCK_APB2_FREQ
#define BOARD_DEBUG_UART_IRQn        UART1_IRQn
#define BOARD_DEBUG_UART_IRQHandler  UART1_IRQHandler

#define BOARD_SPI_MASTER_PORT            SPI3
#define BOARD_SPI_MASTER_BAUDRATE        400000u /* 400khz. */
#define BOARD_SPI_MASTER_FREQ            CLOCK_APB1_FREQ

/* DMA for SPI_XFER. */
#define BOARD_SPI_TX_DMA_PORT        DMA2
#define BOARD_SPI_TX_DMA_CHANNEL     DMA_REQ_DMA2_SPI3_TX
#define BOARD_SPI_TX_DMA_IRQ         DMA2_CH2_IRQn
#define BOARD_DMA_SPI_TX_IRQHandler  DMA2_CH2_IRQHandler
#define BOARD_SPI_RX_DMA_PORT        DMA2
#define BOARD_SPI_RX_DMA_CHANNEL     DMA_REQ_DMA2_SPI3_RX
#define BOARD_SPI_RX_DMA_IRQ         DMA2_CH1_IRQn
#define BOARD_DMA_SPI_RX_IRQHandler  DMA2_CH1_IRQHandler

void BOARD_Init(void);

#endif /* __BOARD_INIT_H__ */

