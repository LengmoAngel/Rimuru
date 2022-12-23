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

#define APP_ADC_SEQ_LEN 1u

/*
 * Variables.
 */

uint32_t app_dma_buff_to[APP_ADC_SEQ_LEN];
volatile bool app_dma_xfer_done = false;

/*
 * Declerations.
 */
void app_adc_init(void);
void app_adc_dma_init(void);

/*
 * Functions.
 */

int main(void)
{
    BOARD_Init();
    printf("adc_dma example. \r\n");

    /* setup adc with dma. */
    app_adc_init();
    printf("press any key to start the conversion.\r\n");
    ADC_DoSwTrigger(BOARD_ADC_PORT, true);

    while (1)
    {
        /* type any key into the terminal to trigger the conversion. */
        getchar();
        printf("dma xfer start...\r\n");

        while (!app_dma_xfer_done)
        {}

        for(uint32_t i = 0; i < APP_ADC_SEQ_LEN; i++)
        {
            printf("adc_val[%u]= %u\r\n", (unsigned)i, (unsigned)(app_dma_buff_to[i]&0xFFF));
        }

        printf("dam xfer done...\r\n");
        app_dma_xfer_done = false;

        ADC_DoSwTrigger(BOARD_ADC_PORT, true);
    }
}

void app_adc_init(void)
{
    /* pins and clock are already in the pin_init.c and clock_init.c. */

    /* setup the DMA for ADC. */
    DMA_Channel_Init_Type dma_channel_init;
    dma_channel_init.MemAddr = (uint32_t)(app_dma_buff_to);
    dma_channel_init.MemAddrIncMode = DMA_AddrIncMode_IncAfterXfer;
    dma_channel_init.PeriphAddr = (uint32_t)&(BOARD_ADC_PORT ->ADDATA); /* ADC data register here. */
    dma_channel_init.PeriphAddrIncMode = DMA_AddrIncMode_StayAfterXfer;
    dma_channel_init.Priority = DMA_Priority_High;
    dma_channel_init.ReloadMode = DMA_ReloadMode_AutoReloadContinuous;
    dma_channel_init.XferCount = APP_ADC_SEQ_LEN;
    dma_channel_init.XferMode = DMA_XferMode_PeriphToMemory;
    dma_channel_init.XferWidth = DMA_XferWidth_32b;
    DMA_InitChannel(BOARD_DMA_ADC_PORT, BOARD_DMA_ADC_CHN, &dma_channel_init);
    DMA_EnableChannel(BOARD_DMA_ADC_PORT, BOARD_DMA_ADC_CHN, true);

    /* enable DMA transfer done interrupt. */
    NVIC_EnableIRQ(BOARD_DMA_ADC_IRQn);
    DMA_EnableChannelInterrupts(BOARD_DMA_ADC_PORT, BOARD_DMA_ADC_CHN, DMA_CHN_INT_XFER_DONE, true);

    /* setup the converter. */
    ADC_Init_Type adc_init;
    adc_init.Resolution = ADC_Resolution_12b;
    adc_init.ClockDiv = ADC_ClockDiv_16;
    adc_init.ConvMode = ADC_ConvMode_Seq; /* run the conversion by sequence. */
    adc_init.Align = ADC_Align_Right;
    ADC_Init(BOARD_ADC_PORT, &adc_init);
    ADC_Enable(BOARD_ADC_PORT, true); /* power on the converter. */

    /* setup the conversion regular sequence channel. */
    ADC_RegSeqConf_Type regseq_conf;
    regseq_conf.SeqSlots = 1u << BOARD_ADC_CHN_NUM;
    regseq_conf.SeqDirection = ADC_RegSeqDirection_LowFirst;
    ADC_EnableRegSeq(BOARD_ADC_PORT, &regseq_conf);

    /* set channel sample time. */
    ADC_SetChnSampleTime(BOARD_ADC_PORT, BOARD_ADC_CHN_NUM, ADC_SampleTime_Alt7);

    /* enable the DMA1 for transporting data. */
    ADC_EnableDMA(BOARD_ADC_PORT, true);

}

/* entry to dma done interrupt. */
void BOARD_DMA_ADC_IRQHandler(void)
{
    ADC_DoSwTrigger(BOARD_ADC_PORT, false);
    if (0u != (DMA_CHN_INT_XFER_DONE & DMA_GetChannelInterruptStatus(BOARD_DMA_ADC_PORT, BOARD_DMA_ADC_CHN)) )
    {
        app_dma_xfer_done = true;
        DMA_ClearChannelInterruptStatus(BOARD_DMA_ADC_PORT, BOARD_DMA_ADC_CHN, DMA_CHN_INT_XFER_DONE);

        /* When enabling the DMA circular mode, the DMA counter and address pointers would be reloaded
         * automatically when the previous transfer sequence is done. The next transfer would be
         * enabled automatically as well. */    }
}

/* EOF. */

