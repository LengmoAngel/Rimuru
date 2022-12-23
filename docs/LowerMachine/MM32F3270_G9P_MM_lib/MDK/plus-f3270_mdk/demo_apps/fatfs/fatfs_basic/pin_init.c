/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_init.h"
#include "hal_rcc.h"
#include "hal_gpio.h"

void BOARD_InitPins(void)
{
    /* PB6 - UART1_TX. */
    GPIO_Init_Type gpio_init;
    gpio_init.Pins  = GPIO_PIN_6;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &gpio_init);
    GPIO_PinAFConf(GPIOB, gpio_init.Pins, GPIO_AF_7);

    /* PB7 - UART1_RX. */
    gpio_init.Pins  = GPIO_PIN_7;
    gpio_init.PinMode  = GPIO_PinMode_In_PullUp;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &gpio_init);
    GPIO_PinAFConf(GPIOB, gpio_init.Pins, GPIO_AF_7);

    /* PC12 - SDIO_CLK. */
    gpio_init.Pins  = GPIO_PIN_12;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &gpio_init);
    GPIO_PinAFConf(GPIOC, GPIO_PIN_12, GPIO_AF_12);

    /* PD2  - SDIO_CMD. */
    gpio_init.Pins  = GPIO_PIN_2;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &gpio_init);
    GPIO_PinAFConf(GPIOD, GPIO_PIN_2, GPIO_AF_12);

    /* PC8  - SDIO_DAT0. */
    gpio_init.Pins  = GPIO_PIN_8;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &gpio_init);
    GPIO_PinAFConf(GPIOC, GPIO_PIN_8, GPIO_AF_12);

    /* PC9  - SDIO_DAT1. */
    gpio_init.Pins  = GPIO_PIN_9;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &gpio_init);
    GPIO_PinAFConf(GPIOC, GPIO_PIN_9, GPIO_AF_12);

    /* PC10 - SDIO_DAT2. */
    gpio_init.Pins  = GPIO_PIN_10;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &gpio_init);
    GPIO_PinAFConf(GPIOC, GPIO_PIN_10, GPIO_AF_12);

    /* PC11 - SDIO_DAT3. */
    gpio_init.Pins  = GPIO_PIN_11;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &gpio_init);
    GPIO_PinAFConf(GPIOC, GPIO_PIN_11, GPIO_AF_12);
}

/* EOF. */
