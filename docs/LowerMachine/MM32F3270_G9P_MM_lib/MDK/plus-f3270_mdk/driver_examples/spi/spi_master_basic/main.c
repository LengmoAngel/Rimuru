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
#define APP_SPI_BUF_LEN 16u /* SPI buffer for SPI tx. */

/*
 * Variables.
 */
uint8_t app_spi_tx_buf[APP_SPI_BUF_LEN]; /* Buffer for SPI tx. */
uint8_t app_spi_rx_buf[APP_SPI_BUF_LEN]; /* Buffer for SPI rx. */
uint32_t app_spi_xfer_err_count; /* Counter for SPI xfer validation. */

/*
 * Declerations.
 */
void app_spi_init(void); /* Setup SPI module. */
void app_spi_putbyte(uint8_t c); /* SPI tx. */
uint8_t app_spi_getbyte(void); /* SPI rx. */

/*
 * Functions.
 */
int main(void)
{
    BOARD_Init();
    
    printf("spi_master_basic example.\r\n");

    /* Setup spi. */
    app_spi_init();
    
    /* Prepare data. */
    for (uint32_t i = 0u; i < APP_SPI_BUF_LEN; i++)
    {
        app_spi_tx_buf[i] = i;
    }

    while (1)
    {
        getchar();

        /* Xfer. */
        for (uint32_t i = 0u; i < APP_SPI_BUF_LEN; i++)
        {
            app_spi_putbyte(app_spi_tx_buf[i]);
            app_spi_rx_buf[i] = app_spi_getbyte();
        }
        
        /* Validation. */
        app_spi_xfer_err_count = 0u;
        for (uint32_t i = 0u; i < APP_SPI_BUF_LEN; i++)
        {
            if (app_spi_rx_buf[i] != app_spi_tx_buf[i])
            {
                app_spi_xfer_err_count++;
            }
        }

        /* Validation result. */
        if (app_spi_xfer_err_count == 0u)
        {
            printf("spi loopback xfer done.\r\n");
        }
        else
        {
            printf("spi loopback xfer error. app_spi_xfer_err_count = %u\r\n", (unsigned)app_spi_xfer_err_count);
        }

        /* Update. */
        for (uint32_t i = 0u; i < APP_SPI_BUF_LEN; i++)
        {
            app_spi_tx_buf[i] = (app_spi_tx_buf[i] + 1u) % APP_SPI_BUF_LEN;
        }
    }
}

/* Setup SPI. */
void app_spi_init(void)
{
    /* Setup SPI module. */
    SPI_Master_Init_Type spi_init;
    spi_init.ClockFreqHz = BOARD_LOOP_SPI_FREQ;
    spi_init.BaudRate = BOARD_LOOP_SPI_BAUDRATE;
    spi_init.XferMode = SPI_XferMode_TxRx;
    spi_init.PolPha = SPI_PolPha_Alt0;
    spi_init.DataWidth = SPI_DataWidth_8b;
    spi_init.LSB = false;
    spi_init.AutoCS = true;
    SPI_InitMaster(BOARD_LOOP_SPI_PORT, &spi_init);

    /* Enable SPI. */
    SPI_Enable(BOARD_LOOP_SPI_PORT, true);
}

/* SPI tx. */
void app_spi_putbyte(uint8_t c)
{
    /* Polling for tx empty. */
    while ( SPI_STATUS_TX_FULL & SPI_GetStatus(BOARD_LOOP_SPI_PORT) )
    {}
    SPI_PutData(BOARD_LOOP_SPI_PORT, c);
}

/* SPI rx. */
uint8_t app_spi_getbyte(void)
{
    /* Polling for rx done. */
    while (0u == (SPI_STATUS_RX_DONE & SPI_GetStatus(BOARD_LOOP_SPI_PORT)) )
    {}
    return SPI_GetData(BOARD_LOOP_SPI_PORT);
}

/* EOF. */

