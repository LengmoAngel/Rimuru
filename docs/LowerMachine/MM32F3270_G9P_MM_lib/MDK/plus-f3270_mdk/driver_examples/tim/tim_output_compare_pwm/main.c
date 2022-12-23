/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <stdio.h>

#include "board_init.h"

#define APP_TIM_STEP_FREQ      1000000u /* 1MHz resolution. */
#define APP_TIM_UPDATE_PERIOD  1000u    /* 1ms period, scale. */

#define APP_TIM_PWM_NUM   8u
uint16_t app_tim_16_pwm_val[APP_TIM_PWM_NUM] =
{
    (APP_TIM_UPDATE_PERIOD >> 3u) * 1u, /* 1/8. */
    (APP_TIM_UPDATE_PERIOD >> 3u) * 2u, /* 2/8. */
    (APP_TIM_UPDATE_PERIOD >> 3u) * 3u, /* 3/8. */
    (APP_TIM_UPDATE_PERIOD >> 3u) * 4u, /* 4/8. */
    (APP_TIM_UPDATE_PERIOD >> 3u) * 5u, /* 5/8. */
    (APP_TIM_UPDATE_PERIOD >> 3u) * 6u, /* 6/8. */
    (APP_TIM_UPDATE_PERIOD >> 3u) * 7u, /* 7/8. */
    APP_TIM_UPDATE_PERIOD,              /* 8/8. */
};

void app_tim_init(void);

/*
 * Functions.
 */

int main(void)
{
    BOARD_Init();
    printf("\r\ntim_output_compare_pwm.\r\n");

    /* Setup the timer. */
    app_tim_init();

    while (1)
    {
        for (uint32_t i = 0; i < APP_TIM_PWM_NUM; i++)
        {
            getchar();
            TIM_PutChannelValue(BOARD_TIM_PORT, BOARD_TIM_CHANNEL, app_tim_16_pwm_val[i]);/* Change duty cycle. */
            printf("PWM value: %u\r\n", (unsigned)app_tim_16_pwm_val[i]);
        }
    }
}

/* Setup the timer. */
void app_tim_init(void)
{
    /* Set the counter counting step. */
    TIM_Init_Type tim_init;
    tim_init.ClockFreqHz = BOARD_TIM_FREQ;
    tim_init.StepFreqHz = APP_TIM_STEP_FREQ;
    tim_init.Period = APP_TIM_UPDATE_PERIOD - 1u;
    tim_init.EnablePreloadPeriod = false;
    tim_init.PeriodMode = TIM_PeriodMode_Continuous;
    tim_init.CountMode = TIM_CountMode_Increasing;
    TIM_Init(BOARD_TIM_PORT, &tim_init);

    /* Set the PWM output channel. */
    TIM_OutputCompareConf_Type tim_outcomp_conf;
    tim_outcomp_conf.ChannelValue = 0u;
    tim_outcomp_conf.EnableFastOutput = false;
    tim_outcomp_conf.EnablePreLoadChannelValue = false; /* Disable preload, put data immediately. */
    tim_outcomp_conf.RefOutMode = TIM_OutputCompareRefOut_FallingEdgeOnMatch;
    tim_outcomp_conf.ClearRefOutOnExtTrigger = false;
    tim_outcomp_conf.PinPolarity = TIM_PinPolarity_Rising;
    TIM_EnableOutputCompare(BOARD_TIM_PORT, BOARD_TIM_CHANNEL, &tim_outcomp_conf);

    /* Start the output compare. */
    TIM_EnableOutputCompareSwitch(BOARD_TIM_PORT, true);

    /* Start the counter. */
    TIM_Start(BOARD_TIM_PORT);
}

/* EOF. */

