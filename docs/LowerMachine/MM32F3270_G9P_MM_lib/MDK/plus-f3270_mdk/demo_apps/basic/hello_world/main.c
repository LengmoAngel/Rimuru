/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

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

/*
 * Functions.
 */
int main(void)
{
    uint8_t ch;

    BOARD_Init();

    printf("hello, world\r\n");

    while (1)
    {
        ch = getchar();
        putchar(ch);
    }
}

/* EOF. */

