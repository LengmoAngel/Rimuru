/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "lcd.h"
#include "board_init.h"

extern void LCD_InitHardware(void);
extern void LCD_WriteCmd(uint16_t cmd);
extern void LCD_WriteData(uint16_t dat);
extern uint16_t LCD_ReadData(void);

uint16_t LCD_ReadReg(uint16_t reg);

void LCD_Init(LCD_Init_Type * init)
{
    LCD_InitHardware();

    GPIO_SetBits(BOARD_LCD_RST_GPIO_PORT, BOARD_LCD_RST_GPIO_PIN);
    GPIO_ClearBits(BOARD_LCD_RST_GPIO_PORT, BOARD_LCD_RST_GPIO_PIN);
    GPIO_SetBits(BOARD_LCD_RST_GPIO_PORT, BOARD_LCD_RST_GPIO_PIN);
    for (uint32_t i = 0u; i < 100000u; i++)
    {
        __NOP();
    }

    LCD_WriteCmd(0x11u);   /*  sleep out. */

    LCD_WriteCmd(0xf0);
    LCD_WriteData(0xc3);

    LCD_WriteCmd(0xf0);
    LCD_WriteData(0x96);

    LCD_WriteCmd(0x2A);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteData( ( (BOARD_LCD_WIDTH >> 8u) & 0xffu ) - 1 );
    LCD_WriteData( ( (BOARD_LCD_WIDTH >> 0u) & 0xffu ) - 1 );
    LCD_WriteCmd(0x2B);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteData( ( (BOARD_LCD_HEIGHT >> 8u) & 0xffu ) - 1 );
    LCD_WriteData( ( (BOARD_LCD_HEIGHT >> 0u) & 0xffu ) - 1 );

    LCD_WriteCmd(0x36);
    if(LCD_DisplayMode_Landspace == init->DisplayMode)
    {
        LCD_WriteData(0x48u);
    }
    else
    {
        LCD_WriteData(0xE8u);
    }

    LCD_WriteData(0x48);

    LCD_WriteCmd(0x3A);
    LCD_WriteData(0x55);

    LCD_WriteCmd(0xB4);
    LCD_WriteData(0x01);

    LCD_WriteCmd(0xB7);
    LCD_WriteData(0xC6);

    LCD_WriteCmd(0xe8);
    LCD_WriteData(0x40);
    LCD_WriteData(0x8a);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteData(0x29);
    LCD_WriteData(0x19);
    LCD_WriteData(0xa5);
    LCD_WriteData(0x33);

    LCD_WriteCmd(0xc2);
    LCD_WriteData(0xA7);

    LCD_WriteCmd(0xc5);
    LCD_WriteData(0x3c);

    LCD_WriteCmd(0xe0);
    LCD_WriteData(0xf0);
    LCD_WriteData(0x00);
    LCD_WriteData(0x02);
    LCD_WriteData(0x0a);
    LCD_WriteData(0x0d);
    LCD_WriteData(0x1d);
    LCD_WriteData(0x35);
    LCD_WriteData(0x55);
    LCD_WriteData(0x45);
    LCD_WriteData(0x3c);
    LCD_WriteData(0x17);
    LCD_WriteData(0x17);
    LCD_WriteData(0x18);
    LCD_WriteData(0x1b);

    LCD_WriteCmd(0xe1);
    LCD_WriteData(0xf0);
    LCD_WriteData(0x00);
    LCD_WriteData(0x02);
    LCD_WriteData(0x07);
    LCD_WriteData(0x06);
    LCD_WriteData(0x04);
    LCD_WriteData(0x2e);
    LCD_WriteData(0x44);
    LCD_WriteData(0x45);
    LCD_WriteData(0x0b);
    LCD_WriteData(0x17);
    LCD_WriteData(0x16);
    LCD_WriteData(0x18);
    LCD_WriteData(0x1b);

    LCD_WriteCmd(0xf0);
    LCD_WriteData(0x3c);

    LCD_WriteCmd(0xf0);
    LCD_WriteData(0x69);

    LCD_WriteCmd(0x29);
}

void LCD_SetWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    LCD_WriteCmd(0x2a);
    LCD_WriteData(x0 >> 8);
    LCD_WriteData(x0 & 0xff);
    LCD_WriteData(x1 >> 8);
    LCD_WriteData(x1 & 0xff);
    LCD_WriteCmd(0x2b);
    LCD_WriteData(y0 >> 8);
    LCD_WriteData(y0 & 0xff);
    LCD_WriteData(y1 >> 8);
    LCD_WriteData(y1 & 0xff);
}

void LCD_ClearWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
    LCD_SetWindow(x0, y0, x1, y1);
    LCD_WriteCmd(0x2c);
    for(uint32_t i = 0; i <= x1 - x0; i++)
    {
        for(uint32_t j = 0; j <= y1 - y0; j++)
        {
            LCD_WriteData(color);
        }
    }
}

void LCD_FillWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t * color)
{
    LCD_SetWindow(x0, y0, x1, y1);
    LCD_WriteCmd(0x2c);
    for(uint32_t i = 0; i <= x1 - x0; i++)
    {
        for(uint32_t j = 0; j <= y1 - y0; j++)
        {
            LCD_WriteData((* color++));
        }
    }
}

void LCD_DrawPixel(uint16_t x, uint16_t y, uint16_t color)
{
    LCD_ClearWindow(x, y, x, y, color);
}



/*  EOF. */
