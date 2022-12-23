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

volatile bool app_adc_conv_done = false;
uint32_t conv_val;

/*
 * Declerations.
 */
void app_adc_init(void);


/*
 * Functions.
 */

int main(void)
{

    BOARD_Init();
    printf("adc_interrupt example. \r\n");
    app_adc_init();
    printf("press any key to start the conversion.\r\n");

    while (1)
    {

        /* type any key into the terminal to trigger the conversion. */
        getchar();

        printf("adc conversion start...\r\n");
        /* start the conversion. */
        ADC_DoSwTrigger(BOARD_ADC_PORT, true);

        /* wait for the conversion done. */
        while (!app_adc_conv_done)
        {}
        app_adc_conv_done = false;
        /* converter done. */
        printf("value=%u\r\n", (unsigned)(conv_val & 0xFFF));
        printf("adc interrupt done...\r\n");
    }
}

void app_adc_init(void)
{

    /* pins and clock are already in the pin_init.c and clock_init.c. */

    /* setup the converter. */
    ADC_Init_Type adc_init;
    adc_init.Resolution = ADC_Resolution_12b;
    adc_init.ClockDiv = ADC_ClockDiv_16;
    adc_init.ConvMode = ADC_ConvMode_SingleSlot;
    adc_init.Align = ADC_Align_Right;
    ADC_Init(BOARD_ADC_PORT, &adc_init);

    ADC_Enable(BOARD_ADC_PORT, true); /* power on the converter. */

    ADC_RegSeqConf_Type regseq_conf;

    /* setup one regular channel. */
    regseq_conf.SeqSlots = 1u << BOARD_ADC_CHN_NUM;
    regseq_conf.SeqDirection = ADC_RegSeqDirection_LowFirst;
    ADC_EnableRegSeq(BOARD_ADC_PORT, &regseq_conf);

    /* set channel sample time. */
    ADC_SetChnSampleTime(BOARD_ADC_PORT, BOARD_ADC_CHN_NUM, ADC_SampleTime_Alt7);
    /* enable ADC interrupt. */
    ADC_EnableInterrupts(BOARD_ADC_PORT, ADC_INT_CONV_SEQ_DONE, true);
    NVIC_EnableIRQ(BOARD_ADC_IRQn);

}

/* entry to adc convert done interrupt. */
void BOARD_ADC_IRQHandler(void)
{
    uint32_t conv_flags;
    uint32_t adc_channel; /* keep the actual hardware conversion channel number. */
    uint32_t flags = ADC_GetStatus(BOARD_ADC_PORT);

    if ( 0u != (flags & ADC_STATUS_CONV_SEQ_DONE) )
    {
        app_adc_conv_done = true;
        conv_val = ADC_GetConvResult(BOARD_ADC_PORT, &adc_channel, &conv_flags);
    }
    ADC_ClearStatus(BOARD_ADC_PORT, flags);
}

/* EOF. */

