/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <stdio.h>

#include "board_init.h"

/*
 * Definitions.
 */


/*
 * Variables.
 */

/*
 * Declerations.
 */

void app_comp_init(void);

/*
 * Functions.
 */

int main(void)
{
    BOARD_Init();

    printf("comp_basic example.\r\n");

    /* Setup comp. */
    app_comp_init();

    printf("press any key to get compare result ...\r\n");

    while (1)
    {
        getchar();
        if ( COMP_GetOutputStatus(BOARD_COMP_PORT, BOARD_COMP_CHN_NUM) )
        {
            printf("- positive.\r\n");
        }
        else
        {
            printf("- inverse.\r\n");
        }
    }
}

void app_comp_init(void)
{
    /* setup the comparator. */
    COMP_Init_Type comp_init;
    comp_init.Hysteresis  = COMP_Hysteresis_Alt3;   /* hysteresis. */
    comp_init.OutMux      = BOARD_COMP_OUT;         /* no output to any TIM. */
    comp_init.PosInMux    = BOARD_COMP_POS_IN;      /* positive side. */
    comp_init.InvInMux    = BOARD_COMP_INV_IN;      /* inverse side. */
    comp_init.Speed       = COMP_Speed_High;        /* the faster the speed, the higher the power consumption. */
    COMP_Init(BOARD_COMP_PORT, BOARD_COMP_CHN_NUM, &comp_init);
    COMP_Enable(BOARD_COMP_PORT, BOARD_COMP_CHN_NUM, true);
}

/* EOF. */
