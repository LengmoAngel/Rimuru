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

void app_iwdg_init(void);
void app_soft_delay(uint32_t delay);

/*
 * Functions.
 */

int main(void)
{
    uint32_t i = 0;

    BOARD_Init();
    printf("iwdg_basic example.\r\n");

    app_iwdg_init();

    for(i = 0; i < 10; i++)
    {
        /* Reload the IWDG counter. */
        IWDG_DoReload(BOARD_IWDG_PORT);
        printf("Feed dog count: %u\r\n", (unsigned)(i+1) );
        app_soft_delay(200);
    }

    /* Waiting for MCU reset. */
    while(1)
    {
    }
}

void app_iwdg_init(void)
{
    /* Setup the IWDG parameters. */
    IWDG_Init_Type iwdg_init;
    iwdg_init.Prescaler = BOARD_IWDG_PRESCALER;
    iwdg_init.Relaod = BOARD_IWDG_RELOAD;

    /* Waiting for reload and prescaler status flags to be cleard. */
    while( 0u != ( (IWDG_STATUS_RELOAD_UPDATE | IWDG_STATUS_PRESCALER_UPDATE) & IWDG_GetStatus(BOARD_IWDG_PORT) ) )
    {
    }
    /* Initialize the IWDG. */
    IWDG_Init(BOARD_IWDG_PORT, &iwdg_init);

    /* Start the IWDG counter. */
    IWDG_Start(BOARD_IWDG_PORT);
}

void app_soft_delay(uint32_t delay)
{
    for(uint32_t i = 0; i < delay; i++)
    {
        for(uint32_t j = 0; j < 10000; j++)
        {
            __NOP();
        }
    }
}

/* EOF. */
