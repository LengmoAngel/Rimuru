/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "board_init.h"

/*
 * Declerations.
 */
void app_dac_init(void);

/*
 * Functions.
 */
int main(void)
{
    BOARD_Init();

    printf("\r\ndac_dual example.\r\n");

    /* Setup the DAC module working with dual mode, to output the triangle wave. */
    app_dac_init();

    while(1)
    {
        getchar();

        /* Get the convertion value. */
        printf("DAC dual outputs :%u and %u.\r\n", (unsigned)DAC_GetData(BOARD_DAC_PORT, DAC_CHN_1), (unsigned)DAC_GetData(BOARD_DAC_PORT, DAC_CHN_2));

        DAC_DoDualChannelSwTrigger(BOARD_DAC_PORT);
    }
}

/* Setup the dual channels of DAC module with the given trigger type. */
void app_dac_init(void)
{
    DAC_Init_Type dac_init;
    DAC_AddTriangle_Init_Type dac_triangle_init;

    /* Setup the DAC_CHANNEL_1. */
    dac_init.EnableOutBuf = false;
    dac_init.TrgSource = BOARD_DAC_TRGSOURCE;
    DAC_Init(BOARD_DAC_PORT, DAC_CHN_1, &dac_init);

    /* Enable additonal feature before enabling the DAC converter. */
    dac_triangle_init.AddTriangle = DAC_AddTriangle_LFSRAmplitude_2047;
    DAC_EnableAddTriangle(BOARD_DAC_PORT, DAC_CHN_1, &dac_triangle_init);
    DAC_Enable(BOARD_DAC_PORT, DAC_CHN_1, true);

    /* Setup the DAC_CHANNEL_2. */
    DAC_Init(BOARD_DAC_PORT, DAC_CHN_2, &dac_init);

    /* Enable additonal feature before enabling the DAC converter. */
    dac_triangle_init.AddTriangle = DAC_AddTriangle_LFSRAmplitude_4095;
    DAC_EnableAddTriangle(BOARD_DAC_PORT, DAC_CHN_2, &dac_triangle_init);
    DAC_Enable(BOARD_DAC_PORT, DAC_CHN_2, true);

    /* Setup the initial value for the dual channel. */
    DAC_PutData(BOARD_DAC_PORT, DAC_CHN_1, BOARD_DAC_WAVE_BASIC, DAC_Align_12b_Dual_Right);
    DAC_DoDualChannelSwTrigger(BOARD_DAC_PORT);/* Do the software trigger to load the setting values. */
}

/* EOF. */

