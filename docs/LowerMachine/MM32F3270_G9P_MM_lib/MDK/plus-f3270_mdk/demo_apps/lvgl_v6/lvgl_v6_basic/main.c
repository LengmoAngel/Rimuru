/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board_init.h"
#include "lvgl.h"
#include "lv_port_disp.h"

/*
 * Macros.
 */

/*
 * Variables.
 */

static const char * btnm_map[] = {"0", "1", "2", "3", "4", "\n",
                                  "5", "6", "7", "8", "9", "\n",
                                  "Action1", "Action2", ""};

/*
 * Declerations.
 */

/*
 * Functions.
 */

void lv_example(void);

/**
 * Create a button with a label and react on click event.
 */

int main(void)
{
    BOARD_Init();

    printf("LVGL basic.\r\n");

    lv_init();
    lv_port_disp_init();
    lv_example();

    while (1)
    {
        lv_task_handler();
    }
}

void lv_example(void)
{
    /* create a label. */
    lv_obj_t * label = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_long_mode(label, LV_LABEL_LONG_SROLL_CIRC);
    lv_obj_set_width(label, 150);
    lv_obj_set_pos(label, 10, 10);
    lv_label_set_text(label, "MindMotion MindMotion");

    /* create a btn matrix. */
    lv_obj_t * btnm1 = lv_btnm_create(lv_scr_act(), NULL);
    lv_btnm_set_map(btnm1, btnm_map);
    lv_btnm_set_btn_width(btnm1, 10, 2);        /*Make "Action1" twice as wide as "Action2"*/
    lv_obj_align(btnm1, NULL, LV_ALIGN_CENTER, 0, 0);
}

void SysTick_Handler(void)
{
    lv_tick_inc(10);
}

/* EOF. */
