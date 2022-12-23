/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <stdio.h>

#include "board_init.h"


/*
 * Definitions.
 */

/*
 * Variables.
 */
uint32_t conv_val;
void app_adc_init(void);
volatile bool app_adc_compare_done = false;

/*
 * Declerations.
 */


/*
 * Functions.
 */

int main(void)
{

    BOARD_Init();
    printf("adc_awdg example. \r\n");

    /* setup adc with dma. */
    app_adc_init();
    printf("press any key to start the conversion.\r\n");

    while(1)
    {
        /* type any key into the terminal to trigger the conversion. */
        getchar();

        /* start the converison. */
        printf("adc conversion start...\r\n");

        ADC_DoSwTrigger(BOARD_ADC_PORT, true);
        printf("Wait for the comparison condition to match...\r\n");

        /* wait for the compare match done. */
        while (!app_adc_compare_done)
        { }

        app_adc_compare_done = false;
        printf("value=%u\n", (unsigned)(conv_val & 0xFFF));
        printf("comparison condition match...\r\n");
    }
}

/* setup the adc converter. */
void app_adc_init(void)
{
    /* pins and clock are already in the pin_init.c and clock_init.c. */

    /* setup the converter. */
    ADC_Init_Type adc_init;

    adc_init.Resolution = ADC_Resolution_12b;
    adc_init.ClockDiv = ADC_ClockDiv_16;
    adc_init.ConvMode = ADC_ConvMode_SeqContinues;
    adc_init.Align = ADC_Align_Right;
    ADC_Init(BOARD_ADC_PORT, &adc_init);

    ADC_Enable(BOARD_ADC_PORT, true); /* power on the converter. */

    /* setup one regular channel. */
    ADC_RegSeqConf_Type regseq_conf;

    regseq_conf.SeqSlots = 1u << BOARD_ADC_HW_COMP_CHN_NUM;
    regseq_conf.SeqDirection = ADC_RegSeqDirection_LowFirst;
    ADC_EnableRegSeq(BOARD_ADC_PORT, &regseq_conf);

    /* set channel sample time. */
    ADC_SetChnSampleTime(BOARD_ADC_PORT, BOARD_ADC_HW_COMP_CHN_NUM, ADC_SampleTime_Alt7);

    /* setup hardware compare. the conversion would be pompt when the conv value is out of windows. */
    ADC_HwCompConf_Type comp_init;
    comp_init.ChnNum    = BOARD_ADC_HW_COMP_CHN_NUM;
    comp_init.HighLimit = BOARD_ADC_HW_COMP_HIGH_LIMIT;
    comp_init.LowLimit  = BOARD_ADC_HW_COMP_LOW_LIMIT;
    ADC_EnableHwComp(BOARD_ADC_PORT, &comp_init);

    /* enable windows compare interrupt. */
    ADC_EnableInterrupts(BOARD_ADC_PORT, ADC_INT_COMPARE_DONE, true);
    NVIC_EnableIRQ(BOARD_ADC_IRQn);
}

/* entry to adc compare done interrupt. */
void BOARD_ADC_IRQHandler(void)
{
    uint32_t conv_flags;
    uint32_t adc_channel; /* keep the actual hardware conversion channel number. */
    uint32_t flags = ADC_GetStatus(BOARD_ADC_PORT);

    if ( 0u != (flags & ADC_STATUS_COMPARE_DONE) )
    {
        app_adc_compare_done = true;
        conv_val = ADC_GetConvResult(BOARD_ADC_PORT, &adc_channel, &conv_flags);
    }

    ADC_ClearStatus(BOARD_ADC_PORT, flags);
}

/* EOF. */

