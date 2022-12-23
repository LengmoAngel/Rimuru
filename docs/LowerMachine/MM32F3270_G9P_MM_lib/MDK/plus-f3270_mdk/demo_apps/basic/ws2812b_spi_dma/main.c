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

void app_delay_ms(uint32_t t);

/*
 * Functions.
 */
int main(void)
{
    BOARD_Init();

    printf("ws2812b example.\r\n");
    
    ws2812b_init();
    ws2812b_display_set_color(WS2812B_COLOR_RED, 0u);
    ws2812b_display_buff_update_all();
    ws2812b_display_start();
    ws2812b_display_waitdone();
    app_delay_ms(100u);

    while (1)
    {
        printf("WS2812B_COLOR_RED\r\n");
        for (uint32_t i = 0u; i < WS2812B_LIST_LED_NUM; i++)
        {
            ws2812b_display_set_color(WS2812B_COLOR_RED, i);
            ws2812b_display_buff_update_all();
            ws2812b_display_start();
            ws2812b_display_waitdone();
            app_delay_ms(100u);
        }
        
        printf("WS2812B_COLOR_GREEN\r\n");
        for (uint32_t i = 0u; i < WS2812B_LIST_LED_NUM; i++)
        {
            ws2812b_display_set_color(WS2812B_COLOR_GREEN, i);
            ws2812b_display_buff_update_all();
            ws2812b_display_start();
            ws2812b_display_waitdone();
            app_delay_ms(100u);
        }
        
        printf("WS2812B_COLOR_BLUE\r\n");
        for (uint32_t i = 0u; i < WS2812B_LIST_LED_NUM; i++)
        {
            ws2812b_display_set_color(WS2812B_COLOR_BLUE, i);
            ws2812b_display_buff_update_all();
            ws2812b_display_start();
            ws2812b_display_waitdone();
            app_delay_ms(100u);
        }
    }
}

void app_delay_ms(uint32_t t)
{
    for (uint32_t i = 0u; i < t; i++)
    {
        for (uint32_t j = 0u; j < 10000U; j++)
        {
            __NOP();
        }
    }
}

/* EOF. */

