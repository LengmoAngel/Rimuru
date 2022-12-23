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
#define APP_I2C_BUF_LEN 8u  /* The size of I2C write and read array. */
#define APP_I2C_TX_LEN 1u  /* The size of I2C write array. */
#define APP_I2C_RX_LEN 1u  /* The size of I2C read array. */

/*
 * Variables.
 */
static I2C_MasterXfer_Type app_i2c_xfer;
volatile static bool app_i2c_xfer_done;  /* Xfer done flag. */
static uint8_t app_i2c_rx_buf[APP_I2C_BUF_LEN];  /* I2C rx buffer. */
static uint8_t app_i2c_tx_buf[APP_I2C_BUF_LEN];  /* I2C tx buffer. */

/*
 * Declerations.
 */
void app_i2c_init(void);
void app_i2c_detect(void);
void app_i2c_rx_abort_callback(void *param);
void app_i2c_rx_done_callback(void *param);
void app_swdelay(uint32_t ms);

/*
 * Functions.
 */
int main(void)
{
    BOARD_Init();
    printf("i2c_master_detect example.\r\n");

    /* Initialize I2C. */
    app_i2c_init();

    while (1)
    {
        printf("press any key to detect I2C.\r\n");
        getchar();
        app_i2c_detect();  /* Detect operation. */
    }
}

/* Detect the operation of write and read. */
void app_i2c_detect()
{
    for (uint16_t i = 0x00u; i <= 0xFEu; i += 2u)  /* 7bit address is (device address >> 1) ,so judge next address need add 2 in address now. */
    {
        printf("target: 0x%02X, ", i);

        app_i2c_xfer.TargetAddr = i >> 1u;          /* Setup target deveice address. */
        app_i2c_xfer.Direction = I2C_Direction_Rx;  /* Setup the xfer direction. */
        app_i2c_xfer.TxBuf = app_i2c_tx_buf;        /* Setup xfer buffer. */
        app_i2c_xfer.RxBuf = app_i2c_rx_buf;        /* Setup rx buffer. */
        app_i2c_xfer.TxLen = APP_I2C_TX_LEN;      /* Setup xfer buffer data length. */
        app_i2c_xfer.RxLen = APP_I2C_RX_LEN;      /* Setup xfer buffer data length. */
        app_i2c_xfer.AbortCallback = app_i2c_rx_abort_callback;  /* Receive abort callback. */
        app_i2c_xfer.DoneCallback = app_i2c_rx_done_callback;    /* Receive done callback. */
        app_i2c_xfer_done = false;                  /* Setup xfer done flag to xfer not done. */

        /* The target device address needs to be configured before enable. */
        I2C_Enable(BOARD_I2C_PORT, false);
        I2C_SetTargetAddr(BOARD_I2C_PORT, app_i2c_xfer.TargetAddr);  /* Set target device address. */
        I2C_Enable(BOARD_I2C_PORT, true);

        I2C_MasterXfer(BOARD_I2C_PORT, &app_i2c_xfer);

        while (false == app_i2c_xfer_done)  /* Waiting for xfer done. */
        {
        }
        app_swdelay(10u);
    }
}

/* Initialize I2C. */
void app_i2c_init(void)
{
    RCC_EnableAPB1Periphs(RCC_APB1_PERIPH_I2C1, true);/* Enable I2C1 clock of APB1 peripheral. */

    I2C_Master_Init_Type i2c_initmaster;

    /* Configure I2C initialization. */
    i2c_initmaster.ClockFreqHz = BOARD_I2C_FREQ;
    i2c_initmaster.BaudRate = I2C_BaudRate_100K;

    /* Initialize I2C master. */
    I2C_InitMaster(BOARD_I2C_PORT, &i2c_initmaster);

    /* Enable I2C. */
    I2C_Enable(BOARD_I2C_PORT, true);

    /* Enable NVIC. */
    NVIC_EnableIRQ(BOARD_I2C_IRQn);
}

/* I2C interrupt handler. */
void BOARD_I2C_IRQHandler(void)
{
    uint32_t flag = I2C_GetInterruptStatus(BOARD_I2C_PORT);  /* Get current interrupt status. */
    I2C_ClearInterruptStatus(BOARD_I2C_PORT, flag);          /* Clear all software clear the interrupt. */
    I2C_MasterXferHandler(BOARD_I2C_PORT, &app_i2c_xfer, flag);  /* I2C master xfer interrupt handler. */
}

/* When I2C received done, use app_i2c_rx_done_callback. */
void app_i2c_rx_done_callback(void *param)
{
    printf("device exists.\r\n");
    app_i2c_xfer_done = true;
}

/* When I2C received abort, use app_i2c_rx_abort_callback. */
void app_i2c_rx_abort_callback(void *param)
{
    printf("device not exists.\r\n");
    app_i2c_xfer_done = true;
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

/* EOF. */

