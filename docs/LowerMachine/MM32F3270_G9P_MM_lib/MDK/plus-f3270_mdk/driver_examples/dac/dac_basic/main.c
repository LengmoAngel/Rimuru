/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "board_init.h"

/*
 * Variables.
 */
uint32_t app_dac_input_value  = 0u;
uint32_t app_dac_output_value = 0u;

/*
 * Declerations.
 */
void     app_dac_init(void);
uint32_t app_dac_output(uint32_t value);

/*
 * Functions.
 */
int main(void)
{
    BOARD_Init();
    printf("\r\ndac_basic example.\r\n");
    /* Enable the DAC module.*/
    app_dac_init();

    while(1)
    {
        getchar();
        /* Put the changed data into the convertion channel and get the convertion channel value back. */
        app_dac_input_value  = (app_dac_input_value + 128u) % 4096u;
        app_dac_output_value = app_dac_output(app_dac_input_value);

        printf("DAC output is : %u.\r\n", (unsigned)app_dac_output_value);
    }
}

/* Init the dual channel of dac module with the give trigger type. */
void app_dac_init(void)
{
    /* Enable the DAC module. */
    DAC_Init_Type dac_init;
    dac_init.EnableOutBuf = false;
    dac_init.TrgSource = DAC_TrgSource_None;

    DAC_Init(BOARD_DAC_PORT, BOARD_DAC_CHANNEL, &dac_init);
    DAC_Enable(BOARD_DAC_PORT, BOARD_DAC_CHANNEL, true);

    /* Clear input register. */
    DAC_PutData(BOARD_DAC_PORT, BOARD_DAC_CHANNEL, 0u, DAC_Align_12b_Right);
}

uint32_t app_dac_output(uint32_t value)
{
    return DAC_PutData(BOARD_DAC_PORT, BOARD_DAC_CHANNEL, value, DAC_Align_12b_Right);
}
/* EOF. */

