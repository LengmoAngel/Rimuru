/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "lcd.h"
#include "board_init.h"

void LCD_InitHardware(void)
{
    FSMC_Init_Type fsmc_init =
    {
        .MemType = FSMC_MemType_SRAM,
        .MemSize = FSMC_MemSize_64MB
    };
    FSMC_Conf_Type fsmc_conf =
    {
        .ReadPeriod    = 0x1u,
        .AddrSetTime   = 0x3u,
        .WriteHoldTime = 0x1u,
        .WritePeriod   = 0x2u,
        .ReadySignal   = FSMC_ReadySignal_Internal,
        .SMReadPipe    = 0u,
        .BusWidth      = FSMC_BusWidth_16b
    };

    FSMC_Init(BOARD_LCD_FSMC_PORT, 3, &fsmc_init);
    FSMC_SetConf(BOARD_LCD_FSMC_PORT, BOARD_LCD_FSMC_SET_INDEX, &fsmc_conf);
    FSMC_EnableConf(BOARD_LCD_FSMC_PORT, 3, BOARD_LCD_FSMC_SET_INDEX);

    GPIO_WriteBit(BOARD_LCD_BL_GPIO_PORT, BOARD_LCD_BL_GPIO_PIN, 1u); /* enable back light. */
}

void LCD_WriteCmd(uint16_t cmd)
{
    FSMC_PutData16(BOARD_LCD_FSMC_PORT, 3, 0, cmd);
}

void LCD_WriteData(uint16_t dat)
{
    FSMC_PutData16(BOARD_LCD_FSMC_PORT, 3, (1u << BOARD_LCD_FSMC_RS_BIT_INDEX), dat);
}

uint16_t LCD_ReadData(void)
{
    return FSMC_GetData16(BOARD_LCD_FSMC_PORT, 3, (1 << BOARD_LCD_FSMC_RS_BIT_INDEX));
}

/* EOF. */
