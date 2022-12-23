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
    GPIO_Init_Type gpio_init;

    /* LEDs. */
    gpio_init.Pins  = GPIO_PIN_2;
    gpio_init.PinMode  = GPIO_PinMode_Out_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOH, &gpio_init);
    GPIO_PinAFConf(GPIOH, gpio_init.Pins, GPIO_AF_15);

    gpio_init.Pins  = GPIO_PIN_15;
    gpio_init.PinMode  = GPIO_PinMode_Out_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpio_init);
    GPIO_PinAFConf(GPIOA, gpio_init.Pins, GPIO_AF_15);

    gpio_init.Pins  = GPIO_PIN_0;
    gpio_init.PinMode  = GPIO_PinMode_Out_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpio_init);
    GPIO_PinAFConf(GPIOA, gpio_init.Pins, GPIO_AF_15);

    gpio_init.Pins  = GPIO_PIN_13;
    gpio_init.PinMode  = GPIO_PinMode_Out_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOG, &gpio_init);
    GPIO_PinAFConf(GPIOG, gpio_init.Pins, GPIO_AF_15);

    /* KEYs. */
    gpio_init.Pins  = GPIO_PIN_7;
    gpio_init.PinMode  = GPIO_PinMode_In_PullUp;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &gpio_init);
    GPIO_PinAFConf(GPIOD, gpio_init.Pins, GPIO_AF_15);

    gpio_init.Pins  = GPIO_PIN_7;
    gpio_init.PinMode  = GPIO_PinMode_In_PullUp;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOG, &gpio_init);
    GPIO_PinAFConf(GPIOG, gpio_init.Pins, GPIO_AF_15);

    gpio_init.Pins  = GPIO_PIN_8;
    gpio_init.PinMode  = GPIO_PinMode_In_PullUp;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOG, &gpio_init);
    GPIO_PinAFConf(GPIOG, gpio_init.Pins, GPIO_AF_15);

    gpio_init.Pins  = GPIO_PIN_9;
    gpio_init.PinMode  = GPIO_PinMode_In_PullUp;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOG, &gpio_init);
    GPIO_PinAFConf(GPIOG, gpio_init.Pins, GPIO_AF_15);

    /* PB6 - UART1_TX. */
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
}

/* EOF. */
