/*
 * Copyright 2022 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board_init.h"
#include "FreeRTOS.h"
#include "task.h"

/*
 * Macros.
 */

/*
 * Variables.
 */

/*
 * Declerations.
 */

/* Task 1: blink LED0. */
void vTask_LED0(void * pvParameters);

/* Task 2: blink LED1. */
void vTask_LED1(void * pvParameters);

/*
 * Functions.
 */
int main(void)
{
    BOARD_Init();

    printf("FreeRTOS basic demo.\r\n");

    /* Create task. */
    xTaskCreate(vTask_LED0, "LED0", 128, NULL, 3, NULL);
    xTaskCreate(vTask_LED1, "LED1", 128, NULL, 3, NULL);

    /* Start scheduler. */
    vTaskStartScheduler();

    while (1)
    {
    }
}

/* Task 1: blink LED0. */
void vTask_LED0(void * pvParameters)
{
    (void)pvParameters;

    while(1)
    {
        led0_onoff(true); /* led on. */
        vTaskDelay(configTICK_RATE_HZ / 2); /* wait 0.5s. */
        led0_onoff(false); /* led off. */
        vTaskDelay(configTICK_RATE_HZ / 2); /* wait 0.5s. */
    }
}

/* Task 2: blink LED1. */
void vTask_LED1(void * pvParameters)
{
    (void)pvParameters;
    while(1)
    {
        led1_onoff(true); /* led on. */
        vTaskDelay(configTICK_RATE_HZ / 5); /* wait 0.2s. */
        led1_onoff(false); /* led off. */
        vTaskDelay(configTICK_RATE_HZ / 5); /* wait 0.2s. */
    }
}

/* EOF. */
