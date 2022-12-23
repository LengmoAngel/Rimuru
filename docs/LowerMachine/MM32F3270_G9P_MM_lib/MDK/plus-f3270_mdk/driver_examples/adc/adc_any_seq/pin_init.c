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

    /* PA0 - ADC channel_1 */
    gpio_init.Pins  = GPIO_PIN_1;
    gpio_init.PinMode  = GPIO_PinMode_In_Analog;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpio_init);

    /* PA2 - ADC channel_2 */
    gpio_init.Pins  = GPIO_PIN_2;
    gpio_init.PinMode  = GPIO_PinMode_In_Analog;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpio_init);

	/* PA5 - ADC channel_5 */
    gpio_init.Pins  = GPIO_PIN_5;
    gpio_init.PinMode  = GPIO_PinMode_In_Analog;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpio_init);
}


/* EOF. */
