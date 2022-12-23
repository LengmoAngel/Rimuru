/*
 * Copyright 2022 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board_init.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/*
 * Macros.
 */

/* The maxmun of goods. */
#define APP_MAX_VACANCY_NUM   3u

/*
 * Variables.
 */

/* semaphore. */
static SemaphoreHandle_t xSemPrintMutex;
static SemaphoreHandle_t xSemVacancy;
static SemaphoreHandle_t xSemProduct;

/*
 * Declerations.
 */

/* Task 1: produce products. */
void vTask_Producer(void * pvParameters);

/* Task 2: consume products. */
void vTask_Consumer(void * pvParameters);

/*
 * Functions.
 */
int main(void)
{
    BOARD_Init();

    printf("FreeRTOS producer consumer demo.\r\n");

    /* Create product semaphore. */
    xSemProduct      = xSemaphoreCreateCounting(APP_MAX_VACANCY_NUM, 0u);
    xSemVacancy      = xSemaphoreCreateCounting(APP_MAX_VACANCY_NUM, APP_MAX_VACANCY_NUM);

    /* Create print semaphore. */
    xSemPrintMutex = xSemaphoreCreateBinary();
    xSemaphoreGive(xSemPrintMutex); /* release print mutex. */

    /* Create task. */
    xTaskCreate(vTask_Producer, "Producer", 128, NULL, 3, NULL);
    xTaskCreate(vTask_Consumer, "Consumer", 128, NULL, 3, NULL);

    /* Start scheduler. */
    vTaskStartScheduler();

    while (1)
    {
    }
}

/* Task 1: produce products. */
void vTask_Producer(void * pvParameters)
{
    (void)pvParameters;

    while(1)
    {
        vTaskDelay(configTICK_RATE_HZ); /* consume a product per second. */

        xSemaphoreTake(xSemVacancy, portMAX_DELAY); /* consumed a vacancy. */
        xSemaphoreGive(xSemProduct); /* produced a product. */

        xSemaphoreTake(xSemPrintMutex, portMAX_DELAY); /* block printf func. */
        printf("The producer has produced a product.\r\n");
        xSemaphoreGive(xSemPrintMutex); /* release printf func. */
    }
}

/* Task 2: consume products. */
void vTask_Consumer(void * pvParameters)
{
    (void)pvParameters;

    while(1)
    {
        vTaskDelay(configTICK_RATE_HZ * 2); /* consume a product per 2s. */

        xSemaphoreTake(xSemProduct, portMAX_DELAY); /* consumed a product. */
        xSemaphoreGive(xSemVacancy); /* produced a vacancy. */

        xSemaphoreTake(xSemPrintMutex, portMAX_DELAY); /* block printf func. */
        printf("Consumed a product.\r\n");
        xSemaphoreGive(xSemPrintMutex); /* release printf func. */
    }
}

/* EOF. */
