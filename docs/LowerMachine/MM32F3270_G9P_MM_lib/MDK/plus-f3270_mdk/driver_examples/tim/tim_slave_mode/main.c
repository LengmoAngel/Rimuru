/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <stdio.h>

#include "board_init.h"


#define APP_TIM_UPDATE_PERIOD  2000u

void app_tim_init(void);

/*
 * Functions.
 */

int main(void)
{
    BOARD_Init();
    printf("\r\ntim_slave_mode.\r\n");

    /* Setup the timer. */
    app_tim_init();

    printf("press input key to stop counting and release to continue counting.\r\n");

    while (1)
    {
    }
}

/* Setup the timer. */
void app_tim_init(void)
{
    /* Set the counter counting step. */
    TIM_Init_Type tim_init;
    tim_init.ClockFreqHz = BOARD_TIM_FREQ;
    tim_init.StepFreqHz = APP_TIM_UPDATE_PERIOD - 1u; /* 1s. */
    tim_init.Period = APP_TIM_UPDATE_PERIOD;
    tim_init.EnablePreloadPeriod = false;
    tim_init.PeriodMode = TIM_PeriodMode_Continuous;
    tim_init.CountMode = TIM_CountMode_Increasing;
    TIM_Init(BOARD_TIM_PORT, &tim_init);

    /* Enable interrupt. */
    NVIC_EnableIRQ(BOARD_TIM_IRQn);
    TIM_EnableInterrupts(BOARD_TIM_PORT, TIM_INT_UPDATE_PERIOD, true);

    /* Enable slave mode. */
    TIM_SlaveModeConf_Type tim_slave_conf;
    tim_slave_conf.In = TIM_SlaveIn_Alt7;/* External trigger pin. */
    tim_slave_conf.Resp = TIM_SlaveResp_Alt5;/* Gated slave mode. */
    TIM_EnableSlaveMode(BOARD_TIM_PORT, &tim_slave_conf);

    /* Start the counter. */
    TIM_Start(BOARD_TIM_PORT);
}

/* TIM_BASIC Period timeout ISR. */
void BOARD_TIM_IRQHandler(void)
{
    uint32_t flags = TIM_GetInterruptStatus(BOARD_TIM_PORT);
    if ( 0u != (flags & TIM_STATUS_UPDATE_PERIOD ) )
    {
        putchar('*');
    }
    TIM_ClearInterruptStatus(BOARD_TIM_PORT, flags);
}

/* EOF. */
