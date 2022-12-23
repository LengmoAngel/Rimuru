/*
 * Copyright 2022 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board_init.h"
#include "sfud.h"
#include "lfs.h"

lfs_t app_lfs;
lfs_file_t app_lfs_file;
struct lfs_config app_lfs_config;

int lfs_flash_init(struct lfs_config *c);

int main(void)
{
    BOARD_Init();
    printf("spi_lfs_sfud_spi example.\r\n");

    int err = lfs_flash_init(&app_lfs_config);
    if (err)
    {
        printf("lfs_flash_init() failed.\r\n");
        while (1);
    }

    err = lfs_mount(&app_lfs, &app_lfs_config);
    if (err)
    {
        printf("lfs_mount() failed.\r\n");
        lfs_format(&app_lfs, &app_lfs_config);
        printf("lfs_format() done.\r\n");
        lfs_mount(&app_lfs, &app_lfs_config);
        printf("lfs_mount() done.\r\n");
    }

    // read current count
    uint32_t boot_count = 0;
    lfs_file_open(&app_lfs, &app_lfs_file, "boot_count", LFS_O_RDWR | LFS_O_CREAT);
    lfs_file_read(&app_lfs, &app_lfs_file, &boot_count, sizeof(boot_count));

    // update boot count
    boot_count += 1;
    lfs_file_rewind(&app_lfs, &app_lfs_file);
    lfs_file_write(&app_lfs, &app_lfs_file, &boot_count, sizeof(boot_count));

    // remember the storage is not updated until the file is closed successfully
    lfs_file_close(&app_lfs, &app_lfs_file);

    // release any resources we were using
    lfs_unmount(&app_lfs);

    // print the boot count
    printf("boot_count: %u\r\n", (unsigned)boot_count);

    while (1)
    {

    }
}

/* EOF. */
