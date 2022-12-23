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
#define APP_SPI_TX_BUFF_LEN 16u /* Tx buffer length. */

/*
 * Variables.
 */
uint8_t app_spi_tx_buf[APP_SPI_TX_BUFF_LEN]; /* SPI tx buffer. */
volatile bool app_dma_xfer_done = false; /* DMA xfer done flag. */

/*
 * Declerations.
 */
void app_spi_tx_dma_init(void); /* Set up SPI and DMA. */
void app_spi_tx_dma_start(void); /* Start DMA xfer. */

/*
 * Functions.
 */
int main(void)
{
    BOARD_Init();
    
    printf("spi_master_tx_dma example.\r\n");

    /* Setup SPI and DMA. */
    app_spi_tx_dma_init();
    
    /* Setup tx data. */
    for (uint32_t i = 0u; i < APP_SPI_TX_BUFF_LEN; i++)
    {
        app_spi_tx_buf[i] = i;
    }

    while (1)
    {
        getchar();

        /* Validation. */
        app_dma_xfer_done = false;
        app_spi_tx_dma_start();
        while (!app_dma_xfer_done)
        {}
        printf("spi tx dma xfer done.\r\n");
    }
}

void app_spi_tx_dma_init(void)
{
    /* Setup DMA. */
    DMA_Channel_Init_Type dma_channel_init;
    dma_channel_init.XferMode = DMA_XferMode_MemoryToPeriph;
    dma_channel_init.ReloadMode = DMA_ReloadMode_AutoReload; /* DMA_AutoReloadMode_Circular */
    dma_channel_init.PeriphAddrIncMode = DMA_AddrIncMode_StayAfterXfer;
    dma_channel_init.MemAddrIncMode = DMA_AddrIncMode_IncAfterXfer;
    dma_channel_init.XferWidth = DMA_XferWidth_8b;
    dma_channel_init.Priority = DMA_Priority_Low;
    dma_channel_init.XferCount = APP_SPI_TX_BUFF_LEN;
    dma_channel_init.MemAddr = (uint32_t)app_spi_tx_buf;
    dma_channel_init.PeriphAddr = SPI_GetTxDataRegAddr(BOARD_SPI_TX_PORT); /* Use tx data register here. */
    DMA_InitChannel(BOARD_SPI_TX_DMA_PORT, BOARD_SPI_TX_DMA_CHANNEL, &dma_channel_init);
    
    /* Enable interrupt for DMA. */
    NVIC_EnableIRQ(BOARD_SPI_TX_DMA_IRQ);
    DMA_EnableChannelInterrupts(BOARD_SPI_TX_DMA_PORT, BOARD_SPI_TX_DMA_CHANNEL, DMA_CHN_INT_XFER_DONE, true);
    
    /* Setup SPI. */
    SPI_Master_Init_Type spi_init;
    spi_init.ClockFreqHz = BOARD_SPI_TX_FREQ;
    spi_init.BaudRate = BOARD_SPI_TX_BAUDRATE;
    spi_init.XferMode = SPI_XferMode_TxRx;
    spi_init.PolPha = SPI_PolPha_Alt0;
    spi_init.DataWidth = SPI_DataWidth_8b;
    spi_init.LSB = false;
    spi_init.AutoCS = true;
    SPI_InitMaster(BOARD_SPI_TX_PORT, &spi_init);
    SPI_EnableDMA(BOARD_SPI_TX_PORT, true); /* Events would trigger the DMA instead of interrupt. */

    /* Enable SPI. */
    SPI_Enable(BOARD_SPI_TX_PORT, true);
}

void app_spi_tx_dma_start(void)
{
    DMA_EnableChannel(BOARD_SPI_TX_DMA_PORT, BOARD_SPI_TX_DMA_CHANNEL, true);
}

/* ISP for SPI_TX DMA done. */
void BOARD_DMA_SPI_TX_IRQHandler(void)
{
    if (0u != (DMA_CHN_INT_XFER_DONE & DMA_GetChannelInterruptStatus(BOARD_SPI_TX_DMA_PORT, BOARD_SPI_TX_DMA_CHANNEL)) )
    {
        app_dma_xfer_done = true;
        DMA_ClearChannelInterruptStatus(BOARD_SPI_TX_DMA_PORT, BOARD_SPI_TX_DMA_CHANNEL, DMA_CHN_INT_XFER_DONE);
    }
}

/* EOF. */

