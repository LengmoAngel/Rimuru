/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <stdio.h>

#include "board_init.h"

#define APP_TIM_UPDATE_PERIOD  2u /* Timeout period length. */

void app_tim_init(void);

/*
 * Functions.
 */

int main(void)
{
    BOARD_Init();
    printf("\r\ntim_external_trigger_input.\r\n");

    /* Setup the timer. */
    app_tim_init();

    printf("press input key to trigger external trigger input and lead an update with indicated period.\r\n");

    while (1)
    {
        getchar();
        printf("counter:%u\r\n", (unsigned)TIM_GetCounterValue(BOARD_TIM_PORT));
    }
}

/* Setup the timer. */
void app_tim_init(void)
{
    /* Set the counter counting step. */
    TIM_Init_Type tim_init;
    tim_init.ClockFreqHz = BOARD_TIM_FREQ;
    tim_init.StepFreqHz = BOARD_TIM_FREQ; /* Should be same with BOARD_TIM_ADV_FREQ if need to count every indicated edge from external trigger. */
    tim_init.Period = APP_TIM_UPDATE_PERIOD - 1u; /* Every APP_TIM_UPDATE_PERIOD press will lead a update interrupt. */
    tim_init.EnablePreloadPeriod = false;
    tim_init.PeriodMode = TIM_PeriodMode_Continuous;
    tim_init.CountMode = TIM_CountMode_Increasing;
    TIM_Init(BOARD_TIM_PORT, &tim_init);

    /* Enable interrupt. */
    NVIC_EnableIRQ(BOARD_TIM_IRQn);
    TIM_EnableInterrupts(BOARD_TIM_PORT, TIM_INT_UPDATE_PERIOD, true);

    /* Enable external trigger input. */
    TIM_ExtTriggerInConf_Type tim_exttrg_input_conf;
    tim_exttrg_input_conf.InDiv = TIM_ExtTriggerInDiv_OnEach1Capture; /* Every external trigger input active edge drives counter adding once. */
    tim_exttrg_input_conf.InFilter = TIM_ExtTriggerInFilter_Alt0; /* No filter. */
    tim_exttrg_input_conf.PinPolarity = TIM_ExtTriggerPinPolarity_Falling; /* Active falling edge. Pressing works, release doesn't work. */
    TIM_EnableExtTriggerIn(BOARD_TIM_PORT, &tim_exttrg_input_conf);

    /* Start the counter. */
    TIM_Start(BOARD_TIM_PORT);
}

/* TIM Period timeout ISR. */
void BOARD_TIM_IRQHandler(void)
{
    uint32_t flags = TIM_GetInterruptStatus(BOARD_TIM_PORT);
    if ( 0u != ( flags & TIM_STATUS_UPDATE_PERIOD ) )
    {
        printf("timeout event happens.\r\n");
    }
    TIM_ClearInterruptStatus(BOARD_TIM_PORT, flags);
}

/* EOF. */
