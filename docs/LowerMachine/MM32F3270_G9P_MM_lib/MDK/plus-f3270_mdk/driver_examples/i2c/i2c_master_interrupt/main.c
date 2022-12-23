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
#define APP_I2C_TARGET_ADDR 0x50u  /* I2C target device address. */
#define APP_I2C_BUF_LEN 32u  /* The size of I2C write and read array. */
#define APP_I2C_TX_LEN 8u   /* The number of tx data. */
#define APP_I2C_RX_LEN 7u  /* The number of rx data. */

/*
 * Variables.
 */
static uint8_t app_i2c_rx_buf[APP_I2C_BUF_LEN];  /* I2C rx buffer. */
static uint8_t app_i2c_tx_buf[APP_I2C_BUF_LEN];  /* I2C tx buffer. */
volatile static bool app_i2c_xfer_done;          /* Xfer done flag. */
static I2C_MasterXfer_Type app_i2c_xfer;

/*
 * Declerations.
 */
void app_i2c_init(void);
void app_i2c_write(void);
void app_i2c_read(void);
void app_i2c_tx_done_callback(void *param);
void app_i2c_tx_abort_callback(void *param);
void app_i2c_rx_done_callback(void *param);
void app_i2c_rx_abort_callback(void *param);
void app_swdelay(uint32_t delay);

/*
 * Functions.
 */
int main(void)
{
    BOARD_Init();
    printf("\r\ni2c_master_interrupt example.\r\n");

    /* Initialize I2C. */
    app_i2c_init();

    for (uint32_t i = 0u; i < APP_I2C_BUF_LEN; i++)   /* Setup the data to be transmitted. */
    {
        app_i2c_tx_buf[i] = i;
    }

    while (1)
    {
        printf("press any key to write i2c-eeprom.\r\n");
        getchar();

        for (uint32_t i = 1u; i < APP_I2C_BUF_LEN; i++)
        {
            app_i2c_tx_buf[i] = (app_i2c_tx_buf[i] + 1u)& 0x7fu;  /* Every time press the key, the value in the current array +1, avoid exceeding 127. */
        }
        app_i2c_write();  /* I2C write data to target device. */
        app_swdelay(10u);   /* Wait for i2c xfer finish. */

        printf("press any key to read i2c-eeprom.\r\n");
        getchar();

        app_i2c_read();  /* I2C read data from target device. */
        app_swdelay(10u);  /* Wait for i2c xfer finish. */
    }
}

/* Initialize I2C. */
void app_i2c_init(void)
{
    /* Setup I2C initialization. */
    I2C_Master_Init_Type i2c_initmaster;
    i2c_initmaster.ClockFreqHz = BOARD_I2C_FREQ;
    i2c_initmaster.BaudRate = I2C_BaudRate_100K;
    app_i2c_xfer.TargetAddr = APP_I2C_TARGET_ADDR;    /* Setup target deveice address. */

    /* Initialize I2C master. */
    I2C_InitMaster(BOARD_I2C_PORT, &i2c_initmaster);

    /* The target device address need to be configured before I2C is enabled. */
    I2C_SetTargetAddr(BOARD_I2C_PORT, app_i2c_xfer.TargetAddr);

    /* Enable I2C. */
    I2C_Enable(BOARD_I2C_PORT, true);

    /* Enable I2C interrupts. */
    NVIC_EnableIRQ(BOARD_I2C_IRQn);
}

/* Put data to device. */
void app_i2c_write(void)
{
    /* Setup I2C tx. */
    app_i2c_xfer.Direction = I2C_Direction_Tx;                 /* Setup the xfer direction. */
    app_i2c_xfer.TxBuf = app_i2c_tx_buf;                       /* Setup tx buffer. */
    app_i2c_xfer.TxLen = APP_I2C_TX_LEN;                       /* Setup the number of data tx. */

    app_i2c_xfer.DoneCallback = app_i2c_tx_done_callback;      /* Transmission abort callback. */
    app_i2c_xfer.AbortCallback = app_i2c_tx_abort_callback;    /* Transmission done callback. */
    app_i2c_xfer_done = false;                                 /* Setup xfer done flag status. */

    I2C_MasterXfer(BOARD_I2C_PORT, &app_i2c_xfer);             /* I2C xfer. */

    while (false == app_i2c_xfer_done)                         /* Wait to xfer done. */
    {
    }
}

/* Get data from device. */
void app_i2c_read(void)
{
    app_i2c_xfer.Direction  = I2C_Direction_Rx;         /* Setup the xfer direction. */
    app_i2c_xfer.TxBuf = app_i2c_tx_buf;                /* Setup tx buffer. */
    app_i2c_xfer.RxBuf = app_i2c_rx_buf;                /* Setup rx buffer. */
    app_i2c_xfer.TxLen = 1;                             /* One data needs to be write to the target address before reading operation. */
    app_i2c_xfer.RxLen = APP_I2C_RX_LEN;                /* Setup the number of receive data. */
    app_i2c_xfer.DoneCallback = app_i2c_rx_done_callback;    /* Transmission abort callback. */
    app_i2c_xfer.AbortCallback = app_i2c_rx_abort_callback;  /* Transmission done callback. */
    app_i2c_xfer_done = false;                               /* Setup xfer done flag status. */

    I2C_MasterXfer(BOARD_I2C_PORT, &app_i2c_xfer);           /* I2C xfer. */

    while (false == app_i2c_xfer_done)  /* Waiting for xfer done. */
    {
    }
}

/* Software delay millisecond. */
void app_swdelay(uint32_t ms)
{
    for (uint32_t i = 0u; i < ms; i++)
    {
        for (uint32_t j = 0u; j < (CLOCK_SYS_FREQ / 1000u); j++)
        {
            __NOP();
        }
    }
}

/* When I2C tx done, use app_i2c_tx_done_callback. */
void app_i2c_tx_done_callback(void *param)
{
    printf("write data: ");
    for (uint32_t i = 0u; i < APP_I2C_TX_LEN; i++)
    {
        printf("0x%02X, ", app_i2c_tx_buf[i]);
    }
    printf("\r\n");
    app_i2c_xfer_done = true;
}

/* When I2C tx abort, use app_i2c_tx_abort_callback. */
void app_i2c_tx_abort_callback(void *param)
{
    printf("tx_abort\r\n");
    app_i2c_xfer_done = true;
}

/* When I2C received done, use app_i2c_rx_done_callback. */
void app_i2c_rx_done_callback(void *param)
{
    printf("read data from device register address: 0x%02X\r\n", app_i2c_tx_buf[0u]);
    printf("read data:  ");
    for (uint32_t i = 0u; i < APP_I2C_RX_LEN; i++)
    {
        printf("0x%02X, ", app_i2c_rx_buf[i]);
    }
    printf("\r\n");
    app_i2c_xfer_done = true;
}

/* When I2C received abort, use app_i2c_rx_abort_callback. */
void app_i2c_rx_abort_callback(void *param)
{
    printf("rx_abort\r\n");
    app_i2c_xfer_done = true;
}

/* I2C interrupt handler */
void BOARD_I2C_IRQHandler(void)
{
    uint32_t flag = I2C_GetInterruptStatus(BOARD_I2C_PORT);      /* Get current interrupt status. */
    I2C_ClearInterruptStatus(BOARD_I2C_PORT, flag);              /* Clear the interrupt flag that can be cleared by software. */
    I2C_MasterXferHandler(BOARD_I2C_PORT, &app_i2c_xfer, flag);  /* I2C master xfer interrupt handler. */
}

/* EOF. */

