/*
 * Copyright 2022 MindMotion Microelectronics Co., Ltd.
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
#include "hal_syscfg.h"
#include "hal_exti.h"
#include "hal_pwr.h"
#include "hal_power.h"

#include "clock_init.h"
#include "pin_init.h"


/* DEBUG UART. */
#define BOARD_DEBUG_UART_PORT        UART1
#define BOARD_DEBUG_UART_BAUDRATE    9600u
#define BOARD_DEBUG_UART_FREQ        CLOCK_APB2_FREQ
#define BOARD_DEBUG_UART_FREQ_2M     2000000

/*SYSCFG*/
#define BOARD_SYSCFG_EXTIPORT        SYSCFG_EXTIPort_GPIOB
#define BOARD_SYSCFG_EXTILINE        SYSCFG_EXTILine_15

/*EXTI*/
#define BOARD_EXTI_PORT              EXTI
#define BOARD_EXTI_LINE              EXTI_LINE_15
#define BOARD_EXTI_IRQN              EXTI15_10_IRQn
#define BOARD_EXTI_IRQHandler        EXTI15_10_IRQHandler

/*POWER*/
#define BOARD_POWER_STANDBYWAKEUP_PORT      PWR_WAKEUP_PIN_5
#define BOARD_POWER_STANDBYWAKEUP_DELAY     PWR_StandbyWakeUpDelay_5

/*
 * Macros.
 */
#define MENU_MESSAGE "\r\nPress:\r\n\
\ta) for Run\r\n\
\tb) for LowPowerRun\r\n\
\tc) for Sleep\r\n\
\td) for LowPowerSleep\r\n\
\te) for Stop\r\n\
\tf) for DeepStop\r\n\
\tg) for Standby\r\n\
-->Pull PB15 down to wake up the MCU from Sleep, LowPowerSleep, Stop, DeepStop or Standby mode.\r\n\
Enter your input:\r\n"

void BOARD_Init(void);
void BOARD_InitDebugConsole(void);
void BOARD_ResetDebugConsole(uint32_t ClockFreq);
void BOARD_PowerModeSelect(uint8_t ch);

#endif /* __BOARD_INIT_H__ */
