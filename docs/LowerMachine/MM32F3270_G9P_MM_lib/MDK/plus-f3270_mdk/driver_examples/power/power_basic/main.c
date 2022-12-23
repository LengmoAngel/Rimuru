/*
 * Copyright 2022 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board_init.h"

/*
 * Definitions.
 */

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

    printf("\r\npower_basic example.\r\n");

    /* set up exti and syscfg. */
    app_exti_init();

    while (1)
    {
        printf(MENU_MESSAGE);

        uint8_t ch = getchar();
        BOARD_PowerModeSelect(ch);
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
    EXTI_EnableLineEvent(BOARD_EXTI_PORT, BOARD_EXTI_LINE, true);

    /* setup NVIC */
    NVIC_EnableIRQ(BOARD_EXTI_IRQN);
}

/* EXTI IRQ Handler */
void BOARD_EXTI_IRQHandler(void)
{
    uint32_t flags = EXTI_GetLineStatus(BOARD_EXTI_PORT);

    EXTI_ClearLineStatus(BOARD_EXTI_PORT, flags);
}

/* EOF. */
