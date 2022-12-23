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

volatile bool app_tim_event_on = false;
void app_tim_init(void);

/*
 * Functions.
 */

int main(void)
{
    BOARD_Init();
    printf("\r\ntim_input_capture example.\r\n");

    /* Setup the timer. */
    app_tim_init();

    printf("press any key to trigger input capture channel ...\r\n");

    while (1)
    {
        while ( !app_tim_event_on )
        {
        }
        app_tim_event_on = false;
        printf("tim input capture event.\r\n");
    }
}

/* Setup the timer. */
void app_tim_init(void)
{
    /* Set the counter counting step. */
    TIM_Init_Type tim_init;
    tim_init.ClockFreqHz = BOARD_TIM_FREQ;
    tim_init.StepFreqHz = APP_TIM_UPDATE_PERIOD;
    tim_init.Period = APP_TIM_UPDATE_PERIOD - 1u;
    tim_init.EnablePreloadPeriod = false;
    tim_init.PeriodMode = TIM_PeriodMode_Continuous;
    tim_init.CountMode = TIM_CountMode_Increasing;
    TIM_Init(BOARD_TIM_PORT, &tim_init);

    /* Enable interrupt. */
    NVIC_EnableIRQ(BOARD_TIM_IRQn);
    TIM_EnableInterrupts(BOARD_TIM_PORT, BOARD_TIM_INT_CHN_EVENT, true);

    /* Enable input capture. */
    TIM_InputCaptureConf_Type tim_input_conf;
    tim_input_conf.InDiv = TIM_InputCaptureInDiv_OnEach1Capture;
    tim_input_conf.InFilter = TIM_InputCaptureInFilter_Alt0;
    tim_input_conf.PinPolarity = TIM_PinPolarity_Falling;
    TIM_EnableInputCapture(BOARD_TIM_PORT, BOARD_TIM_CHANNEL, &tim_input_conf);

    /* Start the counter. */
    TIM_Start(BOARD_TIM_PORT);
}

/* TIM_BASIC Period timeout ISR. */
void BOARD_TIM_IRQHandler(void)
{
    uint32_t flags = TIM_GetInterruptStatus(BOARD_TIM_PORT);
    if ( 0u != ( flags & BOARD_TIM_STATUS_CHN_EVENT ) ) /* Channel capture event. */
    {
        app_tim_event_on = true;
    }
    TIM_ClearInterruptStatus(BOARD_TIM_PORT, flags);
}

/* EOF. */

