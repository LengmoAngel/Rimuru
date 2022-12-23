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
#include "hal_wwdg.h"

#include "clock_init.h"

/* DEBUG UART. */
#define BOARD_DEBUG_UART_PORT        UART1
#define BOARD_DEBUG_UART_BAUDRATE    9600u
#define BOARD_DEBUG_UART_FREQ        CLOCK_APB2_FREQ

/* WWDG */
#define BOARD_WWDG_PORT              WWDG
#define BOARD_WWDG_IRQn              WWDG_IWDG_IRQn
#define BOARD_WWDG_IRQHandler        WWDG_IRQHandler
#define BOARD_WWDG_UPPER_LIMIT       0x7fu
#define BOARD_WWDG_RELOAD_TIMES      100u
#define BOARD_WWDG_RELOAD_VALUE      0x7fu
#define BOARD_WWDG_PRESCALER         WWDG_Prescaler_8

void BOARD_Init(void);

#endif /* __BOARD_INIT_H__ */
