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
#define APP_RTC_LOWEST_YEARS  1970u    /* Setup term of lowest years. */
#define APP_RTC_INIT_YEARS    2008u    /* Setup the clock initial years. */
#define APP_RTC_INIT_MONTHS   12u      /* Setup the clock initial months. */
#define APP_RTC_INIT_DAYS     31u      /* Setup the clock initial days. */
#define APP_RTC_INIT_HOURS    23u      /* Setup the clock initial hours. */
#define APP_RTC_INIT_MINUTES  59u      /* Setup the clock initial minutes. */
#define APP_RTC_INIT_SECONDS  14u      /* Setup the clock initial seconds. */
#define APP_RTC_ALARM_SECONDS 1u       /* Setup the number of seconds from the current time to the alarm response time. */

/*
 * Variables.
 */
RTC_Init_Type rtc_init;
RTC_Time_Type rtc_time;
volatile bool app_rtc_second_done_flag = false;  /* Set seconds interrupt done flag. */
volatile bool app_rtc_alarm_done_flag = false;   /* Set alarm interrupt done flag. */

/*
 * Declerations.
 */
void app_rtc_init(void);
void app_rtc_get_interrupt_current_time(void);
void app_rtc_second_done_callback(void *param);
void app_rtc_alarm_done_callback(void *param);
void app_rtc_alarm_interrupt(void);
void app_rtc_timehandler(uint32_t interrupts);

/*
 * Functions.
 */
int main(void)
{
    uint8_t ch;
    BOARD_Init();
    printf("RTC interrupt example.\r\n");
    printf("Press key 'a' to initialize rtc, 'b' to get current time, 'c' to use alarm clock.\r\n");

    while (1)
    {
        ch = getchar();
        switch(ch)
        {
            case 'a': /* Initialization RTC, use seconds interrupt to count time. */
                printf("a: app_rtc_init().\r\n");
                app_rtc_init();
                printf("RTC init succeed.\r\n");
            break;

            case 'b':  /* Get current time which use seconds interrupt. */
                printf("b: app_rtc_get_interrupt_current_time().\r\n");
                app_rtc_get_interrupt_current_time();
            break;

            case 'c':  /* Get the alarm response time. */
                printf("c: app_rtc_alarm_interrupt().\r\n");
                app_rtc_alarm_interrupt();
                printf("alarm response: ");
            break;

            default:
                printf("a: app_rtc_init().\r\n");
                printf("b: app_rtc_get_interrupt_current_time().\r\n");
                printf("c: app_rtc_alarm_interrupt().\r\n");
                printf("\r\n");
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

/* Initialize RTC clock which use seconds interrupt. */
void app_rtc_init()
{
    rtc_init.ClockFreq            =  APP_RTC_CLOCKFREQ;
    rtc_init.CountFreq            =  APP_RTC_COUNTFREQ;

    rtc_time.Years                =   APP_RTC_INIT_YEARS;
    rtc_time.Months               =   APP_RTC_INIT_MONTHS;
    rtc_time.Days                 =   APP_RTC_INIT_DAYS;
    rtc_time.Hours                =   APP_RTC_INIT_HOURS;
    rtc_time.Mins                 =   APP_RTC_INIT_MINUTES;
    rtc_time.Secs                 =   APP_RTC_INIT_SECONDS;
    rtc_time.Lyears               =   APP_RTC_LOWEST_YEARS;
    app_rtc_second_done_flag      =   false;

    while ( 0u == (RTC_GetStatus(BOARD_RTC_PORT) & RTC_STATUS_SYNC) )  /* Wait for register synchronization. */
    {
    }
    RTC_Init(BOARD_RTC_PORT, &rtc_init);  /* Initialize RTC module. */
    while ( 0u == (RTC_GetStatus(BOARD_RTC_PORT) & RTC_STATUS_OPERATION)  )  /* Wait for write operation finish. */
    {
    }

    /* Enable seconds interrupt. */
    RTC_EnableInterrupts(BOARD_RTC_PORT, RTC_INT_SEC, true);

    /* Wait to register synchronization. Only register synchronization can read RTC register. */
    while ( 0u == (RTC_GetStatus(BOARD_RTC_PORT) & RTC_STATUS_SYNC) )
    {
    }
    RTC_SetTime(BOARD_RTC_PORT, &rtc_time);
    while ( 0u == (RTC_GetStatus(BOARD_RTC_PORT) & RTC_STATUS_OPERATION)  )  /* Wait for write operation finish. */
    {
    }
    NVIC_EnableIRQ(BOARD_RTC_IRQn);  /* Enable NVIC. */

    while (!app_rtc_second_done_flag)  /* Wait for seconds interrupt done. */
    {
    }
}

/* Get the current time in the interrupt processing. If power on again, need to open the access right and enable the interrupt before enter the interrupt processing. */
void app_rtc_get_interrupt_current_time()
{
    /* Setup seconds interrupt. */
    rtc_time.Lyears              =  APP_RTC_LOWEST_YEARS;
    app_rtc_second_done_flag     =  false;

    /* Open access rights. */
    BOARD_RTC_EnableAccess(true);

    NVIC_EnableIRQ(BOARD_RTC_IRQn);    /* Enable seconds interrupt. */
    RTC_EnableInterrupts(BOARD_RTC_PORT, RTC_INT_SEC, true);

    while (!app_rtc_second_done_flag)  /* Wait for second interrupt done. */
    {
    }
}

/* RTC alarm interrupt. */
void app_rtc_alarm_interrupt()
{
    /* Setup alarm interrupt. */
    rtc_time.Lyears             =  APP_RTC_LOWEST_YEARS;
    app_rtc_alarm_done_flag     =  false;
    rtc_time.AlarmTime          =  APP_RTC_ALARM_SECONDS;
    NVIC_EnableIRQ(BOARD_RTC_IRQn);

    /* Open access rights. */
    BOARD_RTC_EnableAccess(true);

    RTC_EnableInterrupts(BOARD_RTC_PORT, RTC_INT_ALARM, true);  /* Enable alarm interrupt. */
    while ( 0u == (RTC_GetStatus(BOARD_RTC_PORT) & RTC_STATUS_SYNC) )  /* Wait for register synchronization, only register synchronization can read RTC register. */
    {
    }
    while ( 0u == (RTC_GetStatus(BOARD_RTC_PORT) & RTC_STATUS_OPERATION) )  /* Wait for write operation finish. */
    {
    }

    RTC_SetAlarm(BOARD_RTC_PORT, &rtc_time);
    while ( 0u == (RTC_GetStatus(BOARD_RTC_PORT) & RTC_STATUS_SYNC) )  /* Wait to register synchronization. Only register synchronization can read RTC register. */
    {
    }
    RTC_CalcTime(BOARD_RTC_PORT, &rtc_time);
    printf("current time is %04d", rtc_time.Years);
    printf("-%02d",    rtc_time.Months);
    printf("-%02d",    rtc_time.Days);
    printf(" %02d",    rtc_time.Hours);
    printf(":%02d",    rtc_time.Mins);
    printf(":%02d\r\n",rtc_time.Secs);

    while (!app_rtc_alarm_done_flag)  /* Wait to alarm interrupt done. */
    {
    }
    RTC_EnableInterrupts(BOARD_RTC_PORT, RTC_INT_ALARM, false);  /* Disable alarm interrupt. */
}

/* Entry to the RTC interrupts. */
void BOARD_RTC_IRQHandler(void)
{
    uint32_t flags = RTC_GetInterruptStatus(BOARD_RTC_PORT);
    app_rtc_timehandler(flags);
}

/* RTC interrupt handler. */
void app_rtc_timehandler(uint32_t interrupts)
{
    /* Alarm interrupt. */
    if (0u != (interrupts & RTC_INT_ALARM) ) /* When the alarm count value is the same as the current count value, the alarm clock interrupt is generated. */
    {
        RTC_ClearInterruptStatus(BOARD_RTC_PORT, RTC_INT_ALARM);  /* Clear alarm interrupt status flag. */
        app_rtc_alarm_done_flag = true;
    }
    /* Seconds interrupt. */
    if ( 0 != (interrupts & RTC_INT_SEC) )
    {
        RTC_CalcTime(BOARD_RTC_PORT, &rtc_time);  /* Get current time. */
        RTC_ClearInterruptStatus(BOARD_RTC_PORT, RTC_INT_SEC | RTC_INT_OVERFLOW);
        app_rtc_second_done_flag = true;
    }
}

/* EOF. */

