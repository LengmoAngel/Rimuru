/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board_init.h"
#include "hal_wwdg.h"

/*
 * Macros.
 */

/*
 * Variables.
 */

volatile static uint32_t reload_times = 0u; /* record the times of WWDG reload. */

/*
 * Declerations.
 */

void app_wwdg_init(void);
void app_soft_delay(uint32_t delay);

/*
 * Functions.
 */

int main(void)
{
    BOARD_Init();
    printf("\r\nwwdg_basic example.\r\n");

    /* Setup WWDG. */
    app_wwdg_init();

    while (1)
    {
        putchar('.');
        app_soft_delay(100);
    }
}

void app_wwdg_init(void)
{
    /* Enbale WWDG. */
    WWDG_Init_Type wwdg_init;
    wwdg_init.Prescaler = BOARD_WWDG_PRESCALER; /* Configure the prescaler of WWDG. */
    wwdg_init.UpperLimit = BOARD_WWDG_UPPER_LIMIT; /* Configure the upper limit value that the window of reload counter. */
    WWDG_Init(BOARD_WWDG_PORT, &wwdg_init);

    /* Enable WWDG interrupt. */
    NVIC_EnableIRQ(BOARD_WWDG_IRQn);
    WWDG_EnableInterrupts(BOARD_WWDG_PORT, WWDG_INT_ALMOST_TIMEOUT, true);

    /* Start counting. */
    WWDG_Start(BOARD_WWDG_PORT);
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

void BOARD_WWDG_IRQHandler(void)
{
    uint32_t status = WWDG_GetStatus(BOARD_WWDG_PORT);
    if( 0 != (WWDG_STATUS_ALMOST_TIMEOUT & status) )
    {
        WWDG_ClearStatus(BOARD_WWDG_PORT, WWDG_STATUS_ALMOST_TIMEOUT);
    }

    /* Stop reload WWDG counter aftert reload WWDG counter BOARD_WWDG_RELOAD_TIMES times. */
    if(BOARD_WWDG_RELOAD_TIMES > reload_times )
    {
        reload_times++;
        WWDG_Reload(BOARD_WWDG_PORT, BOARD_WWDG_RELOAD_VALUE);
    }
}

/* EOF. */
