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
    gpio_init.PinMode  = GPIO_PinMode_In_Floating;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &gpio_init);
    GPIO_PinAFConf(GPIOB, gpio_init.Pins, GPIO_AF_7);

    /* PE3 - SPI_CS. */
    gpio_init.Pins  = GPIO_PIN_3;
    gpio_init.PinMode  = GPIO_PinMode_Out_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &gpio_init);
    GPIO_PinAFConf(GPIOE, gpio_init.Pins, GPIO_AF_15);
    GPIO_SetBits(GPIOE, gpio_init.Pins);

    /* PB10 - SPI_SCK. */
    gpio_init.Pins  = GPIO_PIN_10;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &gpio_init);
    GPIO_PinAFConf(GPIOB, gpio_init.Pins, GPIO_AF_5);

    /* PB14 - SPI_MISO. */
    gpio_init.Pins  = GPIO_PIN_14;
    gpio_init.PinMode  = GPIO_PinMode_In_PullUp;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &gpio_init);
    GPIO_PinAFConf(GPIOB, gpio_init.Pins, GPIO_AF_5);

    /* PB15 - SPI_MOSI. */
    gpio_init.Pins  = GPIO_PIN_15;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &gpio_init);
    GPIO_PinAFConf(GPIOB, gpio_init.Pins, GPIO_AF_5);
}


/* EOF. */
