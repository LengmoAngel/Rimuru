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

    printf("comp_ext_verf example.\r\n");

    /* setup comparator. */
    app_comp_init();

    printf("press any key to get compare result ...\r\n");

    while (1)
    {
        getchar();
        if( COMP_GetOutputStatus(BOARD_COMP_PORT, BOARD_COMP_CHN_NUM) )
        {
            printf("- positive.\r\n");
        }
        else
        {
            printf("- extref.\r\n");
        }
    }
}

void app_comp_init(void)
{
    /* enable the comparator. */
    COMP_Init_Type comp_init;
    comp_init.Hysteresis    = COMP_Hysteresis_Alt3; /* hysteresis. */
    comp_init.OutMux        = BOARD_COMP_OUT;       /* no output. */
    comp_init.PosInMux      = BOARD_COMP_POS_IN;    /* positive side. */
    comp_init.InvInMux      = BOARD_COMP_INV_IN;    /* CRV. */
    comp_init.Speed         = COMP_Speed_High;      /* the faster the speed, the higher the power consumption. */
    COMP_Init(BOARD_COMP_PORT, BOARD_COMP_CHN_NUM, &comp_init);
    COMP_Enable(BOARD_COMP_PORT, BOARD_COMP_CHN_NUM, true);

    /* enable evternal reference voltage source, CRV. */
    COMP_ExtVrefConf_Type comp_extvref_conf;
    comp_extvref_conf.VrefSource = COMP_ExtVrefSource_VDDA;
    comp_extvref_conf.Volt       = BOARD_COMP_EXTVREF_VOLT;
    COMP_EnableExtVrefConf(BOARD_COMP_PORT, &comp_extvref_conf);
}

/* EOF. */
