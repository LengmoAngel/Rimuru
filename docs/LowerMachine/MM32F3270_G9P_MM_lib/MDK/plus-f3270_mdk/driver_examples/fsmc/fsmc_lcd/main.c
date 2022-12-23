/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board_init.h"
#include "lcd.h"

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
    BOARD_Init();

    printf("fsmc lcd example.\r\n");

    /* init the lcd. */
    LCD_Init_Type lcd_init =
    {
        .DisplayMode = LCD_DisplayMode_Landspace,
    };
    LCD_Init(&lcd_init);
    printf("Press any key to fill the screen.\r\n");

    while (1)
    {
        getchar();
        LCD_ClearWindow(0u, 0u, BOARD_LCD_WIDTH-1u, BOARD_LCD_HEIGHT-1u, LCD_COLOR_RED);

        getchar();
        LCD_ClearWindow(0u, 0u, BOARD_LCD_WIDTH-1u, BOARD_LCD_HEIGHT-1u, LCD_COLOR_GREEN);

        getchar();
        LCD_ClearWindow(0u, 0u, BOARD_LCD_WIDTH-1u, BOARD_LCD_HEIGHT-1u, LCD_COLOR_BLUE);
    }
}

/* EOF. */
