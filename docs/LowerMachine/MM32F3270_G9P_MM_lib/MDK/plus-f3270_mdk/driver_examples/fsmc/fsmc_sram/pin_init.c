/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_init.h"
#include "hal_rcc.h"
#include "hal_gpio.h"

/*
 * TXD1 - PB6.
 * RXD1 - PB7.
 */
void BOARD_InitPins(void)
{
    /* PB6 - UART1_TX. */
    GPIO_Init_Type gpio_init;
    gpio_init.Pins     = GPIO_PIN_6;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed    = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &gpio_init);
    GPIO_PinAFConf(GPIOB, gpio_init.Pins, GPIO_AF_7);

    /* PB7 - UART1_RX. */
    gpio_init.Pins  = GPIO_PIN_7;
    gpio_init.PinMode  = GPIO_PinMode_In_Floating;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &gpio_init);
    GPIO_PinAFConf(GPIOB, gpio_init.Pins, GPIO_AF_7);

    /* FSMC_D0  - PD14. */
    gpio_init.Pins  = GPIO_PIN_14;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &gpio_init);
    GPIO_PinAFConf(GPIOD, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_D1  - PD15. */
    gpio_init.Pins  = GPIO_PIN_15;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &gpio_init);
    GPIO_PinAFConf(GPIOD, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_D2  - PD0. */
    gpio_init.Pins  = GPIO_PIN_0;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &gpio_init);
    GPIO_PinAFConf(GPIOD, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_D3  - PD1. */
    gpio_init.Pins  = GPIO_PIN_1;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &gpio_init);
    GPIO_PinAFConf(GPIOD, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_D4  - PE7. */
    gpio_init.Pins  = GPIO_PIN_7;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &gpio_init);
    GPIO_PinAFConf(GPIOE, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_D5  - PE8. */
    gpio_init.Pins  = GPIO_PIN_8;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &gpio_init);
    GPIO_PinAFConf(GPIOE, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_D6  - PE9. */
    gpio_init.Pins  = GPIO_PIN_9;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &gpio_init);
    GPIO_PinAFConf(GPIOE, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_D7  - PE10. */
    gpio_init.Pins  = GPIO_PIN_10;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &gpio_init);
    GPIO_PinAFConf(GPIOE, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_D8  - PE11. */
    gpio_init.Pins  = GPIO_PIN_11;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &gpio_init);
    GPIO_PinAFConf(GPIOE, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_D9  - PE12. */
    gpio_init.Pins  = GPIO_PIN_12;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &gpio_init);
    GPIO_PinAFConf(GPIOE, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_D10 - PE13. */
    gpio_init.Pins  = GPIO_PIN_13;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &gpio_init);
    GPIO_PinAFConf(GPIOE, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_D11 - PE14. */
    gpio_init.Pins  = GPIO_PIN_14;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &gpio_init);
    GPIO_PinAFConf(GPIOE, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_D12 - PE15. */
    gpio_init.Pins  = GPIO_PIN_15;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &gpio_init);
    GPIO_PinAFConf(GPIOE, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_D13 - PD8. */
    gpio_init.Pins  = GPIO_PIN_8;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &gpio_init);
    GPIO_PinAFConf(GPIOD, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_D14 - PD9. */
    gpio_init.Pins  = GPIO_PIN_9;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &gpio_init);
    GPIO_PinAFConf(GPIOD, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_D15 - PD10. */
    gpio_init.Pins  = GPIO_PIN_10;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &gpio_init);
    GPIO_PinAFConf(GPIOD, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_RS(A0)  - PF0. */
    gpio_init.Pins  = GPIO_PIN_0;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOF, &gpio_init);
    GPIO_PinAFConf(GPIOF, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_RS(A1)  - PF1. */
    gpio_init.Pins  = GPIO_PIN_1;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOF, &gpio_init);
    GPIO_PinAFConf(GPIOF, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_RS(A2)  - PF2. */
    gpio_init.Pins  = GPIO_PIN_2;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOF, &gpio_init);
    GPIO_PinAFConf(GPIOF, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_RS(A3)  - PF3. */
    gpio_init.Pins  = GPIO_PIN_3;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOF, &gpio_init);
    GPIO_PinAFConf(GPIOF, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_RS(A4)  - PF4. */
    gpio_init.Pins  = GPIO_PIN_4;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOF, &gpio_init);
    GPIO_PinAFConf(GPIOF, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_RS(A5)  - PF5. */
    gpio_init.Pins  = GPIO_PIN_5;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOF, &gpio_init);
    GPIO_PinAFConf(GPIOF, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_RS(A6)  - PF12. */
    gpio_init.Pins  = GPIO_PIN_12;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOF, &gpio_init);
    GPIO_PinAFConf(GPIOF, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_RS(A7)  - PF13. */
    gpio_init.Pins  = GPIO_PIN_13;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOF, &gpio_init);
    GPIO_PinAFConf(GPIOF, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_RS(A8)  - PF14. */
    gpio_init.Pins  = GPIO_PIN_14;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOF, &gpio_init);
    GPIO_PinAFConf(GPIOF, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_RS(A9)  - PF15. */
    gpio_init.Pins  = GPIO_PIN_15;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOF, &gpio_init);
    GPIO_PinAFConf(GPIOF, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_RS(A10)  - PG0. */
    gpio_init.Pins  = GPIO_PIN_0;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOG, &gpio_init);
    GPIO_PinAFConf(GPIOG, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_RS(A11)  - PG1. */
    gpio_init.Pins  = GPIO_PIN_1;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOG, &gpio_init);
    GPIO_PinAFConf(GPIOG, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_RS(A12)  - PG2. */
    gpio_init.Pins  = GPIO_PIN_2;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOG, &gpio_init);
    GPIO_PinAFConf(GPIOG, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_RS(A13)  - PG3. */
    gpio_init.Pins  = GPIO_PIN_3;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOG, &gpio_init);
    GPIO_PinAFConf(GPIOG, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_RS(A14)  - PG4. */
    gpio_init.Pins  = GPIO_PIN_4;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOG, &gpio_init);
    GPIO_PinAFConf(GPIOG, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_RS(A15)  - PG5. */
    gpio_init.Pins  = GPIO_PIN_5;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOG, &gpio_init);
    GPIO_PinAFConf(GPIOG, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_RS(A16)  - PD11. */
    gpio_init.Pins  = GPIO_PIN_11;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &gpio_init);
    GPIO_PinAFConf(GPIOD, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_RS(A17)  - PD12. */
    gpio_init.Pins  = GPIO_PIN_12;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &gpio_init);
    GPIO_PinAFConf(GPIOD, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_RS(A18)  - PD13. */
    gpio_init.Pins  = GPIO_PIN_13;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &gpio_init);
    GPIO_PinAFConf(GPIOD, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_CS  - PG10. */
    gpio_init.Pins  = GPIO_PIN_10;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOG, &gpio_init);
    GPIO_PinAFConf(GPIOG, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_NOE - PD4. */
    gpio_init.Pins  = GPIO_PIN_4;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &gpio_init);
    GPIO_PinAFConf(GPIOD, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_NWE - PD5. */
    gpio_init.Pins  = GPIO_PIN_5;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &gpio_init);
    GPIO_PinAFConf(GPIOD, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_NBL0 - PE0. */
    gpio_init.Pins  = GPIO_PIN_0;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &gpio_init);
    GPIO_PinAFConf(GPIOE, gpio_init.Pins, GPIO_AF_12);

    /* FSMC_NBL1 - PE1. */
    gpio_init.Pins  = GPIO_PIN_1;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &gpio_init);
    GPIO_PinAFConf(GPIOE, gpio_init.Pins, GPIO_AF_12);

}


/* EOF. */
