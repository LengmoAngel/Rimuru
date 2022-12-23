/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board_init.h"


/*
 * Definitions.
 */
volatile bool app_exti_event_on = false; /* interrupt status. */
volatile uint32_t app_exti_event_times = 0u; /* counting interrupt times. */

/*
 * Declerations.
 */
void app_exti_init(void);

/*
 * Functions.
 */
int main(void)
{
    BOARD_Init();

    printf("\r\nexti_basic example.\r\n");

    /* set up exti and syscfg. */
    app_exti_init();

    while (1)
    {
        while ( !app_exti_event_on ) /* check interrupt status. */
        {
        }
        app_exti_event_on = false; /* clear status. */
        app_exti_event_times += 1u; /* accumulation. */
        printf("exti interrupt times:%u.\r\n", (unsigned)app_exti_event_times);
    }
}

/* setup the external interrupt and system conf. */
void app_exti_init(void)
{
    /* setup syscfg for port and line. */
    SYSCFG_SetExtIntMux(BOARD_SYSCFG_EXTIPORT, BOARD_SYSCFG_EXTILINE);

    /* setup exti and enable. */
    EXTI_SetTriggerIn(BOARD_EXTI_PORT, BOARD_EXTI_LINE, EXTI_TriggerIn_FallingEdge);
    EXTI_EnableLineInterrupt(BOARD_EXTI_PORT, BOARD_EXTI_LINE, true);

    /* setup NVIC */
    NVIC_EnableIRQ(BOARD_EXTI_IRQN);
}

/* EXTI IRQ Handler */
void BOARD_EXTI_IRQHandler(void)
{
    uint32_t flags = EXTI_GetLineStatus(BOARD_EXTI_PORT);
    if ( 0u != ( flags & BOARD_EXTI_LINE ) ) /* Interrupts. */
    {
        app_exti_event_on = true;
    }
    EXTI_ClearLineStatus(BOARD_EXTI_PORT, flags);
}

/* EOF. */

