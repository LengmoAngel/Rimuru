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
 * Macros.
 */
#define APP_I2C_TARGET_ADDR  0x50u  /* I2C target device address. */
#define APP_I2C_BUF_LEN  16u        /* The size of I2C write and read array. */
#define APP_I2C_TIMEOUT_TIME 3000u  /* Wait for the time when the status flag appears. If exceeds time, don't wait any longer and return to timeout. */
#define APP_I2C_TX_LEN  8u          /* The number of tx data. */
#define APP_I2C_RX_LEN  7u          /* The number of rx data. */

/*
 * Variables.
 */
static uint8_t app_i2c_rx_buf[APP_I2C_BUF_LEN]; /* I2C rx buffer. */
static uint8_t app_i2c_tx_buf[APP_I2C_BUF_LEN]; /* I2C tx buffer. */
static I2C_MasterXfer_Type app_i2c_xfer;

/*
 * Declerations.
 */
void app_i2c_init(void);
bool app_i2c_write(uint8_t txlen, uint8_t *txbuf);
bool app_i2c_read(uint8_t rxlen, uint8_t *rxbuf);

/*
 * Functions.
 */
int main(void)
{
    BOARD_Init();
    printf("\r\ni2c_master_basic example\r\n");

    /* Initialize I2C. */
    app_i2c_init();

    /* Setup the data to be transmitted. */
    for (uint32_t i = 0u; i < APP_I2C_BUF_LEN; i++)
    {
        app_i2c_tx_buf[i] = i;
    }

    while (1)
    {
        printf("press any key to write i2c-eeprom.\r\n");
        getchar();

        for (uint32_t i = 1u; i < APP_I2C_BUF_LEN; i++)
        {
            app_i2c_tx_buf[i] = (app_i2c_tx_buf[i] + 2u) & 0x7fu;  /* Every time press the key, the data in the current array +1, avoid exceeding 127. */
        }

        /* Write data to target device. */
        if ( false == app_i2c_write(APP_I2C_TX_LEN, app_i2c_tx_buf) )
        {
            printf("I2C write failed.\r\n");
        }
        else
        {
            printf("write data: ");
            for (uint32_t i = 0u; i < APP_I2C_TX_LEN; i++)
            {
                printf("0x%02X, ", app_i2c_tx_buf[i]);
            }
            printf("\r\n");
        }

        printf("press any key to read i2c-eeprom.\r\n");
        getchar();

        /* Read data from target device. */
        if ( false == app_i2c_read(APP_I2C_RX_LEN, app_i2c_rx_buf) )  /* Received data successfully. */
        {
            printf("I2C read failed.\r\n");
        }
        else
        {
            printf("read data from device register address: 0x%02X\r\n", app_i2c_tx_buf[0u]);
            printf("read data:  ");
            for (uint32_t i = 0u; i < APP_I2C_RX_LEN; i++)
            {
                printf("0x%02X, ", app_i2c_rx_buf[i]);
            }
            printf("\r\n");
        }
    }
}

/* Initialize I2C */
void app_i2c_init(void)
{
    /* Setup I2C initialization values. */
    I2C_Master_Init_Type i2c_init;
    i2c_init.ClockFreqHz = BOARD_I2C_FREQ;
    i2c_init.BaudRate = I2C_BaudRate_100K;

    /* Initialize I2C master. */
    I2C_InitMaster(BOARD_I2C_PORT, &i2c_init);

    /* The target device address needs to be configured before enabling. */
    I2C_SetTargetAddr(BOARD_I2C_PORT, APP_I2C_TARGET_ADDR);

    /* Enable I2C. */
    I2C_Enable(BOARD_I2C_PORT, true);
}

/* Write data to target device, true to writing succeed, false to writing failed. */
bool app_i2c_write(uint8_t txlen, uint8_t *txbuf)
{
    app_i2c_xfer.WaitTimes = APP_I2C_TIMEOUT_TIME;
    app_i2c_xfer.TxBuf = txbuf;
    app_i2c_xfer.TxLen = txlen;

    I2C_Enable(BOARD_I2C_PORT, true);  /* Disable I2C to clear tx fifo, and enabled I2C to perform the write operation again. */
    if ( false == I2C_MasterWriteBlocking(BOARD_I2C_PORT, &app_i2c_xfer) )
    {
        return false;
    }
    else
    {
        return true;
    }
}

/* Read data to target device, true to reading succeed, false to reading failed. */
bool app_i2c_read(uint8_t rxlen, uint8_t *rxbuf)
{
    app_i2c_xfer.WaitTimes = APP_I2C_TIMEOUT_TIME;
    app_i2c_xfer.RxBuf = rxbuf;
    app_i2c_xfer.RxLen = rxlen;

    I2C_Enable(BOARD_I2C_PORT, true);  /* Disable I2C to clear tx fifo, and enabled I2C to perform the read operation again. */
    if ( false == I2C_MasterReadBlocking(BOARD_I2C_PORT, &app_i2c_xfer) )
    {
        return false;
    }
    else
    {
        return true;
    }
}

/* EOF. */

