/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board_init.h"




/*
 * Macros.
 */
#define APP_DMA_BUFF_COUNT    16u

/*
 * Variables.
 */
uint32_t app_dma_buff_from[APP_DMA_BUFF_COUNT];
uint32_t app_dma_buff_to[APP_DMA_BUFF_COUNT];

/*
 * Declerations.
 */
void    app_dma_init(void); 
void    app_dma_start(void);

/*
 * Functions.
 */
int main(void)
{
    uint8_t c;

    BOARD_Init();

    printf("\r\ndma_burst_basic example.\r\n");
    printf("watch the memory of \"app_dma_buff_to[]\" and press any key to start the dma transfer with given value ...\r\n");

    app_dma_init();

    for (uint32_t i = 0u; i < APP_DMA_BUFF_COUNT; i++)
    {
        app_dma_buff_from[i] = i;
        app_dma_buff_to[i] = 0u;
    }
    
    while (1)
    {
        c = getchar();
        putchar(c);
        
        /* clear the target memory. */
        for (uint32_t i = 0u; i < APP_DMA_BUFF_COUNT; i++)
        {
            app_dma_buff_to[i] = 0u;
        }
        
        app_dma_start();
    }
}

void app_dma_init(void)
{
    DMA_Channel_Init_Type dma_channel_init;
    
    dma_channel_init.XferMode = DMA_XferMode_MemoryToPeriphBurst;
    dma_channel_init.ReloadMode = DMA_ReloadMode_AutoReload; /* DMA_AutoReloadMode_Circular */
    dma_channel_init.PeriphAddrIncMode = DMA_AddrIncMode_IncAfterXfer;
    dma_channel_init.MemAddrIncMode = DMA_AddrIncMode_IncAfterXfer;
    dma_channel_init.XferWidth = DMA_XferWidth_32b;
    dma_channel_init.Priority = DMA_Priority_Low;
    dma_channel_init.XferCount = APP_DMA_BUFF_COUNT;
    dma_channel_init.MemAddr = (uint32_t)app_dma_buff_from;
    dma_channel_init.PeriphAddr = (uint32_t)app_dma_buff_to;
    DMA_InitChannel(BOARD_DMA_PORT, BOARD_DMA_CHANNEL, &dma_channel_init);
}

/* Trigger the DMA to move data. */
void app_dma_start(void)
{
    DMA_EnableChannel(BOARD_DMA_PORT, BOARD_DMA_CHANNEL, true);

    /* The channel would be disabled automatically when the xfer is done. */
}

/* EOF. */

