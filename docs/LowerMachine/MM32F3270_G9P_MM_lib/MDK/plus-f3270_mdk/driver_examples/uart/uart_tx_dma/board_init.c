/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board_init.h"
#include "clock_init.h"
#include "pin_init.h"

#include "hal_rcc.h"
#include "hal_gpio.h"
#include "hal_uart.h"

/*
 * Macros.
 */

#define BOARD_LED_TICK_IN_SYSTICK_TICKS  100u /* 1s. */

/*
 * Variables.
 */

volatile uint32_t led_timeout_ticks;
volatile uint32_t systick_ticks;

/*
 * Declerations.
 */
void BOARD_InitLed(void);

/*
* Functions.
*/
void BOARD_Init(void)
{
    BOARD_InitBootClocks();
    BOARD_InitPins();
    
    BOARD_InitLed();
    
    /* Systick时钟固定是AHB时钟的8分频。AHB freq = 96mhz. */
    systick_ticks = 0u;
    SysTick_Config(CLOCK_SYSTICK_FREQ / BOARD_LED_TICK_IN_SYSTICK_TICKS); /* 100hz, 10ms per tick. */
}


void BOARD_InitLed(void)
{
    led_timeout_ticks = 0u;
    GPIO_WriteBit(BOARD_LED0_GPIO_PORT, BOARD_LED0_GPIO_PIN, 1u);
}

/* turn on the led and turn off later automatically when timeout. */
void BOARD_LedOnTimeout(uint32_t ticks)
{

    GPIO_WriteBit(BOARD_LED0_GPIO_PORT, BOARD_LED0_GPIO_PIN, 0u); /* led on. */
    if (ticks == 0u)
    {
        led_timeout_ticks = 0u; /* always on. */
    }
    else
    {
        led_timeout_ticks = ticks * 2u - 1u;
        systick_ticks = 0u; /* reset the systick timer. */
    }
}


/* SysTick ISR entry. */
void SysTick_Handler(void)
{
    if (systick_ticks >= BOARD_LED_TICK_IN_SYSTICK_TICKS)
    {
        systick_ticks = 0u;
        
        if ( led_timeout_ticks != 0u)
        {
            if ( (led_timeout_ticks % 2u) == 1u )
            {
                GPIO_WriteBit(BOARD_LED0_GPIO_PORT, BOARD_LED0_GPIO_PIN, 1u);
            }
            else
            {
                GPIO_WriteBit(BOARD_LED0_GPIO_PORT, BOARD_LED0_GPIO_PIN, 0u);
            }
            led_timeout_ticks--;
        }
    }
    systick_ticks++;
}

/* EOF. */

