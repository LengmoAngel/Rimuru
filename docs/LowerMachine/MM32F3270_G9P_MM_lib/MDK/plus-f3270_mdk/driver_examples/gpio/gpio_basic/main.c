/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <stdio.h>

#include "board_init.h"

/*
 * Definitions.
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
int main(void)
{
    BOARD_Init();

    printf("\r\ngpio_basic example.\r\n");

    while (1)
    {
        if ( GPIO_ReadInDataBit(BOARD_KEY0_GPIO_PORT, BOARD_KEY0_GPIO_PIN) ) /* key is no pressed. */
        {
            GPIO_WriteBit(BOARD_LED0_GPIO_PORT, BOARD_LED0_GPIO_PIN, 1u); /* led off. */
            GPIO_WriteBit(BOARD_LED1_GPIO_PORT, BOARD_LED1_GPIO_PIN, 0u); /* led on. */
        }
        else /* key is pressed. */
        {
            GPIO_WriteBit(BOARD_LED0_GPIO_PORT, BOARD_LED0_GPIO_PIN, 0u); /* led on. */
            GPIO_WriteBit(BOARD_LED1_GPIO_PORT, BOARD_LED1_GPIO_PIN, 1u); /* led off. */
        }
    }
}

/* EOF. */

