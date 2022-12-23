/*
 * Copyright 2022 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board_init.h"

#include "sfud.h"

/*
 * Macros.
 */

#define APP_SFUD_SECTOR_SIZE   4096u /* the size of sector. */
#define APP_SFUD_PAGE_SIZE     256u  /* the size of page. */

/*
 * Variables.
 */

/* the string of operation info. */
const char str_erase_sector[]            = "a. Erase Sector.\r\n";
const char str_write_page[]              = "b. Write page.\r\n";
const char str_read_page[]               = "c. Read page.\r\n";
const char str_change_sector_index[]     = "d. Change sector index.\r\n";
const char str_change_page_index[]       = "e. Change page index.\r\n";
const char str_change_write_buf[]        = "f. Change write buffer.\r\n";
const char str_reset_sector_page_index[] = "g. Reset sector & page index.\r\n";
const char str_sector_index[]            = "The sector index is %u.\r\n";
const char str_page_index[]              = "The page index is %u.\r\n";
const char str_done[]                    = "Done.\r\n";

/* the buf for test sfud write & qspi read. */
static uint8_t sfud_write_buf[APP_SFUD_PAGE_SIZE];
static uint8_t sfud_read_buf[APP_SFUD_PAGE_SIZE];

static uint32_t sector_index = 0u; /* the sector index of erase, read & write. */
static uint32_t page_index = 0u;   /* the page index of read & write. */

/*
 * Declerations.
 */

void app_sfud_task(uint8_t ch);

/*
 * Functions.
 */

int main(void)
{
    uint8_t ch = 0u;
    BOARD_Init();

    printf("\r\nspiflash_sfud_qspi example.\r\n");

    sfud_init(); /* init sfud. */

    /* assign value to write buf. */
    for (uint32_t i = 0; i < APP_SFUD_PAGE_SIZE; i++)
    {
        sfud_write_buf[i] = i % 0x100;
    }

    /* print help. */
    printf(str_erase_sector);
    printf(str_write_page);
    printf(str_read_page);
    printf(str_change_sector_index);
    printf(str_change_page_index);
    printf(str_change_write_buf);
    printf(str_reset_sector_page_index);

    /* run sfud task. */
    while (1)
    {
        ch = getchar();
        app_sfud_task(ch);
    }
}

void app_sfud_task(uint8_t ch)
{
    switch (ch)
    {
        case 'a': /* erase flash. */
            printf(str_erase_sector);
            printf(str_sector_index, (unsigned)sector_index);

            /* sfud erase. */
            sfud_erase(sfud_get_device(SFUD_SPI_DEVICE_INDEX), sector_index * APP_SFUD_SECTOR_SIZE, APP_SFUD_SECTOR_SIZE);

            printf(str_done);
            break;
        case 'b': /* write flash. */
            printf(str_write_page);
            printf(str_sector_index, (unsigned)sector_index);
            printf(str_page_index, (unsigned)page_index);

            /* sfud write. */
            sfud_write(sfud_get_device(SFUD_SPI_DEVICE_INDEX), sector_index * APP_SFUD_SECTOR_SIZE + page_index * APP_SFUD_PAGE_SIZE, APP_SFUD_PAGE_SIZE, sfud_write_buf);

            printf(str_done);
            break;
        case 'c': /* read flash. */
            printf(str_read_page);
            printf(str_sector_index, (unsigned)sector_index);
            printf(str_page_index, (unsigned)page_index);
            /* sfud read. */
            sfud_read(sfud_get_device(SFUD_SPI_DEVICE_INDEX), sector_index * APP_SFUD_SECTOR_SIZE + page_index * APP_SFUD_PAGE_SIZE, APP_SFUD_PAGE_SIZE, sfud_read_buf);

            for(uint32_t i = 0u; i < APP_SFUD_PAGE_SIZE; i++)
            {
                if (0 == i % 16u)
                {
                    printf("\r\n");
                }
                printf("%02X ",sfud_read_buf[i]);
            }
            printf("\r\n");
            printf(str_done);
            break;
        case 'd': /* change sector index. */
            printf(str_change_sector_index);
            sector_index++;
            printf(str_sector_index, (unsigned)sector_index);
            printf(str_done);
            break;
        case 'e': /* change page index. */
            printf(str_change_page_index);
            page_index++;
            if (page_index > (APP_SFUD_SECTOR_SIZE / APP_SFUD_PAGE_SIZE) )
            {
                page_index = 0u;
            }
            printf(str_page_index, (unsigned)page_index);
            printf(str_done);
            break;
        case 'f': /* change write buf content. */
            printf(str_change_write_buf);
            for (uint32_t i = 0; i < APP_SFUD_PAGE_SIZE; i++)
            {
                sfud_write_buf[i] = (sfud_write_buf[i] + 1u) % 0x100;
                if (0 == i % 16u)
                {
                    printf("\r\n");
                }
                printf("%02X ",sfud_write_buf[i]);
            }
            printf("\r\n");
            printf(str_done);
            break;
        case 'g': /* reset sector & page index. */
            printf(str_reset_sector_page_index);
            sector_index = 0u;
            page_index = 0u;
            printf(str_sector_index, (unsigned)sector_index);
            printf(str_page_index, (unsigned)page_index);
            printf(str_done);
            break;
        default: /* print help. */
            printf(str_erase_sector);
            printf(str_write_page);
            printf(str_read_page);
            printf(str_change_sector_index);
            printf(str_change_page_index);
            printf(str_change_write_buf);
            printf(str_reset_sector_page_index);

            break;
    }
}

/* EOF. */
