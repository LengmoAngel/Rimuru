/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board_init.h"
#include "clock_init.h"
#include "pin_init.h"

#include "hal_rcc.h"
#include "hal_gpio.h"
#include "hal_uart.h"

/*
 * Macros.
 */

/*
 * Variables.
 */

/*
 * Declerations.
 */

/*
* Functions.
*/
void BOARD_Init(void)
{
    BOARD_InitBootClocks();
    BOARD_InitPins();
}

/* EOF. */
