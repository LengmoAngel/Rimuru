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

/*
 * Declerations.
 */
void     app_adc_init(void);
uint32_t app_adc_run_conv(void);


/*
 * Functions.
 */

int main(void)
{
    BOARD_Init();
    printf("adc_basic example.\r\n");

    app_adc_init();
    printf("press any key to start the conversion.\r\n");

    while (1)
    {
        /* type any key into the terminal to trigger the conversion. */
        getchar();

        /* satrt the one channel conversion. */
        printf("app_adc_run_conv() start...\r\n");
        printf("adc_val= %u\r\n", (unsigned)(app_adc_run_conv() & 0xFFF));
        printf("app_adc_run_conv() done.\r\n\r\n");
    }
}

/* setup the adc converter, and prepare a regular conversion sequence with only one channel in. */
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
    ADC_EnableTempSensor(BOARD_ADC_PORT, true); /* enable the temperature sensor. */

    /* setup the sequence, a regular conversion with only one channel. */
    ADC_RegSeqConf_Type adc_regseq_conf;
    adc_regseq_conf.SeqSlots = 1u << BOARD_ADC_CHN_NUM;
    adc_regseq_conf.SeqDirection = ADC_RegSeqDirection_LowFirst;
    ADC_EnableRegSeq(BOARD_ADC_PORT, &adc_regseq_conf);

    /* set channel sample time. */
    ADC_SetChnSampleTime(BOARD_ADC_PORT, BOARD_ADC_CHN_NUM, ADC_SampleTime_Alt7);
}

/* software tirgger the adc converter and start the sequence conversion. */
uint32_t app_adc_run_conv(void)
{
    uint32_t data;
    uint32_t flags;
    uint32_t adc_channel; /* keep the actual hardware conversion channel number. */

    /* software tirgger the conversion. */
    ADC_DoSwTrigger(BOARD_ADC_PORT, true);

    /* wait while the conversion is ongoing. */
    while( 0u == (ADC_GetStatus(BOARD_ADC_PORT) & ADC_STATUS_CONV_SEQ_DONE) )
    {}

    ADC_ClearStatus(BOARD_ADC_PORT, ADC_STATUS_CONV_SEQ_DONE);

    data = ADC_GetConvResult(BOARD_ADC_PORT, &adc_channel, &flags);

    if (0u == (flags & ADC_CONV_RESULT_FLAG_VALID) )
    {
        data = 0u; /* the data is unavailable when the VALID flag is not on. */
    }

    return data;
}

/* EOF. */

