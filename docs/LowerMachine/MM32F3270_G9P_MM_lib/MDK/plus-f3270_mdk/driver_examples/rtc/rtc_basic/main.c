/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <stdio.h>
#include "board_init.h"
#include "hal_rtc.h"

/*
 * Macros.
 */
#define APP_RTC_CLOCKFREQ     32768u   /* Due to the formula: ftrue_clk = frtc_clk /(prescaler + 1), configure the clock to jump once a second. */
#define APP_RTC_COUNTFREQ     1u       /* Configure the counter frequency, the counter jumps once every second at the fastest.. */
#define APP_RTC_LOWEST_YEARS  1970u    /* Set term of lowest years. */
#define APP_RTC_INIT_YEARS    2008u    /* Configure the clock initial years. */
#define APP_RTC_INIT_MONTHS   12u      /* Configure the clock initial months. */
#define APP_RTC_INIT_DAYS     31u      /* Configure the clock initial days. */
#define APP_RTC_INIT_HOURS    23u      /* Configure the clock initial hours. */
#define APP_RTC_INIT_MINUTES  59u      /* Configure the clock initial minutes. */
#define APP_RTC_INIT_SECONDS  15u      /* Configure the clock initial seconds. */

/*
 * Variables.
 */
RTC_Init_Type rtc_init;
RTC_Time_Type rtc_time;

/*
 * Declerations.
 */
void app_rtc_init(void);
void app_rtc_get_current_time(void);

/*
 * Functions.
 */
int main(void)
{
    uint8_t ch;
    BOARD_Init();
    printf("rtc_basic example.\r\n");
    printf("Press key 'a' to initialize rtc, 'b' to get current time.\r\n");

    while (1)
    {
        ch = getchar();
        switch(ch)
        {
            case 'a':  /* Initialize RTC. */
                app_rtc_init();
                printf("a: app_rtc_init().\r\n");
                app_rtc_get_current_time();
            break;

            case 'b':  /* Get current clock time. */
                printf("b: app_rtc_get_current_time().\r\n");
                app_rtc_get_current_time();
            break;

            default:
                printf("case a: app_rtc_init().\r\n");
                printf("case b: app_rtc_get_current_time().\r\n");
            break;
        }
        printf("%04d",     rtc_time.Years);
        printf("-%02d",    rtc_time.Months);
        printf("-%02d",    rtc_time.Days);
        printf(" %02d",    rtc_time.Hours);
        printf(":%02d",    rtc_time.Mins);
        printf(":%02d\r\n",rtc_time.Secs);
    }
}

/* initialization RTC time. */
void app_rtc_init(void)
{
    rtc_init.ClockFreq     =  APP_RTC_CLOCKFREQ;
    rtc_init.CountFreq     =  APP_RTC_COUNTFREQ;

    /* Setup RTC clock initialization time. */
    rtc_time.Years         =  APP_RTC_INIT_YEARS;
    rtc_time.Months        =  APP_RTC_INIT_MONTHS;
    rtc_time.Days          =  APP_RTC_INIT_DAYS;
    rtc_time.Hours         =  APP_RTC_INIT_HOURS;
    rtc_time.Mins          =  APP_RTC_INIT_MINUTES;
    rtc_time.Secs          =  APP_RTC_INIT_SECONDS;
    rtc_time.Lyears        =  APP_RTC_LOWEST_YEARS;

    while ( 0u == (RTC_GetStatus(BOARD_RTC_PORT) & RTC_STATUS_SYNC) ) /* Wait for register synchronization. */
    {
    }

    RTC_Init(BOARD_RTC_PORT, &rtc_init);    /* Initialize RTC. */
    while ( 0u == (RTC_GetStatus(BOARD_RTC_PORT) & RTC_STATUS_OPERATION)  )  /* Wait for write operation finish. */
    {
    }

    /* Wait for register synchronization. Only register synchronization can read RTC register. */
    while ( 0u == (RTC_GetStatus(BOARD_RTC_PORT) & RTC_STATUS_SYNC) )
    {
    }
    RTC_SetTime(BOARD_RTC_PORT, &rtc_time);
    while ( 0u == (RTC_GetStatus(BOARD_RTC_PORT) & RTC_STATUS_OPERATION)  )  /* Wait for write operation finish. */
    {
    }
}

/* Get current time of RTC. */
void app_rtc_get_current_time()
{
    rtc_time.Lyears  = APP_RTC_LOWEST_YEARS;
    while ( 0u == (RTC_GetStatus(BOARD_RTC_PORT) & RTC_STATUS_SYNC) )  /* Wait to register synchronization. Only register synchronization can read RTC register. */
    {
    }
    RTC_CalcTime(BOARD_RTC_PORT, &rtc_time);
}

/* EOF. */

