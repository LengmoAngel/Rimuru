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
void app_delay(uint32_t t);

uint32_t app_tim_counter_val = 0u;
TIM_EncoderDirection_Type app_tim_encoder_dir = TIM_EncoderDirection_Backward;

/*
 * Functions.
 */

int main(void)
{
    BOARD_Init();
    printf("\r\ntim_slave_mode_encoder.\r\n");

    /* Setup the timer. */
    app_tim_init();
    
    while (1)
    {
        GPIO_WriteBit(BOARD_TIM_CHN_PORT, BOARD_TIM_CHN_1_PIN, 1u); /* Channel 1 has a rising edge when channel 2 is low. Counter direction is forward. */
        app_delay(100);

        GPIO_WriteBit(BOARD_TIM_CHN_PORT, BOARD_TIM_CHN_2_PIN, 1u); /* Channel 2 has a rising edge when channel 1 is high. Counter direction is forward. */
        app_delay(100);

        GPIO_WriteBit(BOARD_TIM_CHN_PORT, BOARD_TIM_CHN_1_PIN, 0u); /* Channel 1 has a falling edge when channel 2 is high. Counter direction is forward. */
        app_delay(100);

        GPIO_WriteBit(BOARD_TIM_CHN_PORT, BOARD_TIM_CHN_2_PIN, 0u); /* Channel 2 has a falling edge when channel 1 is low. Counter direction is forward. */
        app_delay(100);

        getchar();
        if ( ( app_tim_encoder_dir = TIM_GetEncoder(BOARD_TIM_PORT, &app_tim_counter_val) ) == TIM_EncoderDirection_Forward )
        {
            printf("moving direction is forward with pulse times:%u.\r\n", (unsigned)app_tim_counter_val);
        }
        else
        {
            printf("moving direction is backward with pulse times:%u.\r\n", (unsigned)app_tim_counter_val);
        }
    }
}

/* Use cpu running here for delay. */
void app_delay(uint32_t t)
{
    for (uint32_t i = 0u; i < t; i++)
    {
        for (uint32_t j = 0u; j < 1000u; j++)
        {
            __NOP();
        }
    }
}

/* Setup the timer. */
void app_tim_init(void)
{
    /* Set the counter counting step. */
    TIM_Init_Type tim_init;
    tim_init.ClockFreqHz = BOARD_TIM_FREQ;
    tim_init.StepFreqHz = BOARD_TIM_FREQ; /* StepFreqHz would not affect. */
    tim_init.Period = APP_TIM_UPDATE_PERIOD - 1u;
    tim_init.EnablePreloadPeriod = false;
    tim_init.PeriodMode = TIM_PeriodMode_Continuous;
    tim_init.CountMode = TIM_CountMode_Increasing; /* If choose center aligned mode will lead to free run mode, which means adding until 0xffff. */
    TIM_Init(BOARD_TIM_PORT, &tim_init);

    /* Enable interrupt. */
    NVIC_EnableIRQ(BOARD_TIM_IRQn);
    TIM_EnableInterrupts(BOARD_TIM_PORT, TIM_INT_UPDATE_PERIOD, true);

    /* Enable input capture. */
    TIM_InputCaptureConf_Type tim_input_conf;
    tim_input_conf.InDiv = TIM_InputCaptureInDiv_OnEach1Capture;
    tim_input_conf.InFilter = TIM_InputCaptureInFilter_Alt0;
    tim_input_conf.PinPolarity = TIM_PinPolarity_Rising; /* Switch to TIM_PinPolarity_Falling if need reversing the channel 1 input for underflow of the counter. */
    TIM_EnableInputCapture(BOARD_TIM_PORT, BOARD_TIM_CHN_1, &tim_input_conf);
    tim_input_conf.PinPolarity = TIM_PinPolarity_Rising;
    TIM_EnableInputCapture(BOARD_TIM_PORT, BOARD_TIM_CHN_2, &tim_input_conf);

    /* Enable slave mode. */
    TIM_SlaveModeConf_Type tim_slave_conf;
    tim_slave_conf.In = TIM_SlaveIn_Alt0;/* Input would not afferct under encoder mode. */
    tim_slave_conf.Resp = TIM_SlaveResp_Alt3;/* Encoder mode 3. */
    TIM_EnableSlaveMode(BOARD_TIM_PORT, &tim_slave_conf);

    /* Start the counter. */
    TIM_Start(BOARD_TIM_PORT);
}

/* TIM Period timeout ISR. */
void BOARD_TIM_IRQHandler(void)
{
    uint32_t flags = TIM_GetInterruptStatus(BOARD_TIM_PORT);
    if ( 0u != (flags & TIM_STATUS_UPDATE_PERIOD ) ) /* Check update status. */
    {
        printf("update\r\n");
    }
    TIM_ClearInterruptStatus(BOARD_TIM_PORT, flags);
}
/* EOF. */

