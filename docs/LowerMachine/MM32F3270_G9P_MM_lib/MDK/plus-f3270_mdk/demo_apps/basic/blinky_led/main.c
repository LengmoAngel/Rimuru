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
 * Macros.
 */

/*
 * Variables.
 */

/*
 * Declerations.
 */

void app_delay(uint32_t t);

/*
 * Functions.
 */

int main(void)
{
    uint8_t ch;
    BOARD_Init();

    leds_init();

    printf("hello world");
    while (1)
    {
        ch = getchar();
        putchar(ch);
        leds_on();  app_delay(100);
        leds_off(); app_delay(100);
    }
}

/* Use cpu running here to see the speed of instruments. */
void app_delay(uint32_t t)
{
    for (uint32_t i = 0u; i < t; i++)
    {
        for (uint32_t j = 0u; j < 10000u; j++)
        {
            __NOP();
        }
    }
}

/* EOF. */

