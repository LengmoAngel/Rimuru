/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __LCD_H__
#define __LCD_H__

#include "hal_common.h"

/*+----- X ---->
 *|
 *Y  LCD screen.
 *|
 *v
*/

#define LCD_COLOR_WHITE          0xFFFF
#define LCD_COLOR_BLACK          0x0000
#define LCD_COLOR_BLUE           0x001F
#define LCD_COLOR_BRED           0xF81F
#define LCD_COLOR_GRED           0xFFE0
#define LCD_COLOR_GBLUE          0x07FF
#define LCD_COLOR_RED            0xF800
#define LCD_COLOR_MAGENTA        0xF81F
#define LCD_COLOR_GREEN          0x07E0
#define LCD_COLOR_CYAN           0x7FFF
#define LCD_COLOR_YELLOW         0xFFE0
#define LCD_COLOR_BROWN          0xBC40
#define LCD_COLOR_BRRED          0xFC07
#define LCD_COLOR_GRAY           0x8430

typedef enum
{
    LCD_DisplayMode_Portrait = 0u,
    LCD_DisplayMode_Landspace = 1u,
} LCD_DisplayMode_Type;

typedef struct
{
    LCD_DisplayMode_Type DisplayMode;
} LCD_Init_Type;

void LCD_Init(LCD_Init_Type * lcd_init);
void LCD_SetWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
void LCD_ClearWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
void LCD_FillWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t * color);
void LCD_DrawPixel(uint16_t x, uint16_t y, uint16_t color);

#endif /* __LCD_H__ */
