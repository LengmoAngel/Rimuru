/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "board_init.h"

/*
 * Definitions.
 */
#define APP_DAC_BUFF_COUNT    13u

/*
 * Variables.
 */
uint32_t app_dac_buff_from[APP_DAC_BUFF_COUNT];
volatile bool app_dma_xfer_done;

/*
 * Declerations.
 */
void app_dac_init(void);
void app_dac_dma_start(void);

/*
 * Functions.
 */
int main(void)
{
    BOARD_Init();
    printf("\r\ndac_dma example.\r\n");

    /* Lable the dma transfer flag false. */
    app_dma_xfer_done = false;

    /* Prepare data. */
    for(uint32_t i = 0u; i < APP_DAC_BUFF_COUNT; i++)
    {
        app_dac_buff_from[i] = ( 1u << i ) - 1u;
    }

    /* Setup the DAC module. */
    app_dac_init();

    while (1)
    {
        getchar();
        /* Software trigger the convertion. */
        DAC_DoSwTrigger(BOARD_DAC_PORT, BOARD_DAC_CHANNEL);
        printf("DAC transfers one data.\r\n");
        /* Moniter the transfer. */
        if (app_dma_xfer_done)
        {
            printf("DMA transfer finished.\r\n");
            /* Reset the flag and restart transfer. */
            app_dma_xfer_done = false;

            app_dac_dma_start();
        }
    }
}

void app_dac_init(void)
{
    /* Setup the DAC_CHANNEL_1. */
    DAC_Init_Type dac_init;
    dac_init.EnableOutBuf = false;
    dac_init.TrgSource = BOARD_DAC_TRGSOURCE;

    DAC_Init(BOARD_DAC_PORT, BOARD_DAC_CHANNEL, &dac_init);
    DAC_Enable(BOARD_DAC_PORT, BOARD_DAC_CHANNEL, true);

    /* Enable the DMA function on DAC. */
    DAC_EnableDMA(BOARD_DAC_PORT, BOARD_DAC_CHANNEL, true);

    /* Init DMA. */
    DMA_Channel_Init_Type dma_channel_init;

    dma_channel_init.XferMode          = DMA_XferMode_MemoryToPeriph;
    dma_channel_init.ReloadMode        = DMA_ReloadMode_AutoReloadContinuous;
    dma_channel_init.PeriphAddrIncMode = DMA_AddrIncMode_StayAfterXfer;
    dma_channel_init.MemAddrIncMode = DMA_AddrIncMode_IncAfterXfer;
    dma_channel_init.XferWidth         = DMA_XferWidth_32b;
    dma_channel_init.Priority          = DMA_Priority_Low;
    dma_channel_init.XferCount         = APP_DAC_BUFF_COUNT;
    dma_channel_init.MemAddr        = (uint32_t)app_dac_buff_from;
    dma_channel_init.PeriphAddr        = (uint32_t)DAC_GetDataRegAddr(BOARD_DAC_PORT, BOARD_DAC_CHANNEL, DAC_Align_12b_Right);

    DMA_InitChannel(BOARD_DMA_DAC_PORT, BOARD_DMA_DAC_CHANNEL, &dma_channel_init);

    /* Enable Interrupts. */
    DMA_EnableChannelInterrupts(BOARD_DMA_DAC_PORT, BOARD_DMA_DAC_CHANNEL, DMA_CHN_INT_XFER_DONE, true);
    NVIC_EnableIRQ(BOARD_DMA_DAC_IRQn);

    DMA_EnableChannel(BOARD_DMA_DAC_PORT, BOARD_DMA_DAC_CHANNEL, true);
}

/* DMA Interrupt requst. */
void BOARD_DMA_DAC_IRQHandler(void)
{
    if (0u != (DMA_CHN_INT_XFER_DONE & DMA_GetChannelInterruptStatus(BOARD_DMA_DAC_PORT, BOARD_DMA_DAC_CHANNEL)) )
    {
        /* Label the transfer flag. */
        app_dma_xfer_done = true;
        DMA_ClearChannelInterruptStatus(BOARD_DMA_DAC_PORT, BOARD_DMA_DAC_CHANNEL, DMA_CHN_INT_XFER_DONE);
    }
}

/* Start the dma transfer. */
void app_dac_dma_start(void)
{
    DMA_EnableChannel(BOARD_DMA_DAC_PORT, BOARD_DMA_DAC_CHANNEL, true);
}

/* EOF. */

