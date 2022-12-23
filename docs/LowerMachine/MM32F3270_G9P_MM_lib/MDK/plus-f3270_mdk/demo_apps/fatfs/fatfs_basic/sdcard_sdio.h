/*
 * Copyright 2022 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __SDCARD_SDIO_H__
#define __SDCARD_SDIO_H__

#include "hal_common.h"

#define SDCARD_BLOCK_SIZE 512u

typedef enum
{
    sdcard_cardtype_sdsc,
    sdcard_cardtype_sdhc,
    sdcard_cardtype_sdxc,
} sdcard_cardtype_t;

typedef struct
{
    void * iodev;
    sdcard_cardtype_t cardtype;
    uint32_t block_cnt;
    uint32_t block_len;
    uint32_t rca; /* relative card address. */

} sdcard_t;

bool sdcard_init(sdcard_t * card, void * iodev);
bool sdcard_write_single_block(sdcard_t * card, uint32_t blk_idx, uint8_t * out_buf);
bool sdcard_write_multi_blocks(sdcard_t * card, uint32_t blk_idx, uint32_t blk_cnt, uint8_t * out_buf);
bool sdcard_read_single_block(sdcard_t * card, uint32_t blk_idx, uint8_t * in_buf);
bool sdcard_read_multi_blocks(sdcard_t * card, uint32_t blk_idx, uint32_t blk_cnt, uint8_t * in_buf);

#endif /* __SDCARD_SDIO_H__ */
