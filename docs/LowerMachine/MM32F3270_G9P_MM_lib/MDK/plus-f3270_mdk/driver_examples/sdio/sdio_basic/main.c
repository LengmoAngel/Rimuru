/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <stdint.h>
#include <stdio.h>

#include "board_init.h"
#include "sdcard_sdio.h"

/*
 * Definitions.
 */

/*
 * Variables.
 */

sdcard_t app_sdcard;
uint8_t app_sdcard_read_buf[SDCARD_BLOCK_SIZE*2];
uint8_t app_sdcard_write_buf[SDCARD_BLOCK_SIZE*2];

uint8_t app_test_dat8[4] = {0x11, 0x22, 0x33, 0x44};

uint32_t app_sdcard_write_blk_idx = 0u;
uint32_t app_sdcard_read_blk_idx = 0u;
uint8_t  app_sdcard_write_seed = 0u;



/*
 * Declerations.
 */

/*
 * Functions.
 */
int main(void)
{
    uint8_t c;
    uint32_t tmp32;

    BOARD_Init();

    printf("\r\nsdio_basic example project.\r\n");
    
    sdcard_init(&app_sdcard, BOARD_SDCARD_SDIO_PORT);
    printf("sdcard_init() done.\r\n");
    
    while (1)
    {
        c = getchar();
        switch (c)
        {
            case 'a': /* read single block. */
                printf("a: read single block.\r\n");

                printf("reading block num: %u\r\n", (unsigned)app_sdcard_read_blk_idx);
                sdcard_read_single_block(&app_sdcard, app_sdcard_read_blk_idx++, app_sdcard_read_buf);
                for (uint32_t i = 0u; i < SDCARD_BLOCK_SIZE; i++)
                {
                    if ( (i % 16) == 0u)
                    {
                        printf("\r\n");
                    }
                    printf("0x%2X, ", app_sdcard_read_buf[i]);
                }

                printf("\r\n\r\n");
            
                break;

            case 'b': /* read multiple blocks. */
                printf("b: sdcard_read_multi_blocks().\r\n");

                printf("reading block num: %u, %u\r\n", (unsigned)app_sdcard_read_blk_idx, (unsigned)app_sdcard_read_blk_idx+1u);
                sdcard_read_multi_blocks(&app_sdcard, app_sdcard_read_blk_idx, 2u, app_sdcard_read_buf);
                app_sdcard_read_blk_idx += 2u;
                for (uint32_t i = 0u; i < SDCARD_BLOCK_SIZE*2u; i++)
                {
                    if ( (i % 16) == 0u)
                    {
                        printf("\r\n");
                    }
                    printf("0x%2X, ", app_sdcard_read_buf[i]);
                }
                printf("\r\n\r\n");

                break;

            case 'c': /* write single block. */
                printf("c: sdcard_write_single_block.\r\n");

                printf("writing block num: %u\r\n", (unsigned)app_sdcard_write_blk_idx);
                tmp32 = app_sdcard_write_seed;
                for (uint32_t i = 0u; i < SDCARD_BLOCK_SIZE; i++)
                {
                    app_sdcard_write_buf[i] = (tmp32++) % 256;
                }

                sdcard_write_single_block(&app_sdcard, app_sdcard_write_blk_idx++, app_sdcard_write_buf);
                printf("write done.\r\n\r\n");

                break;

            case 'd': /* write multiple blocks. */
                printf("d: sdcard_write_multi_blocks().\r\n");

                printf("writing block num: %u, %u\r\n", (unsigned)app_sdcard_write_blk_idx, (unsigned)app_sdcard_write_blk_idx+1);
                tmp32 = app_sdcard_write_seed;
                for (uint32_t i = 0u; i < SDCARD_BLOCK_SIZE*2u; i++)
                {
                    app_sdcard_write_buf[i] = (tmp32++) % 256;
                }

                sdcard_write_multi_blocks(&app_sdcard, app_sdcard_write_blk_idx, 2u, app_sdcard_write_buf);
                app_sdcard_write_blk_idx += 2u;

                break;

            case 'e':
                printf("e: sdcard_init().\r\n");
                sdcard_init(&app_sdcard, BOARD_SDCARD_SDIO_PORT);
                printf("done.\r\n");
                break;            

            case 'f':
                printf("f: reset the read/write index.\r\n");
                app_sdcard_write_blk_idx = 0u;
                app_sdcard_read_blk_idx = 0u;
                break;

            case 'g':
                printf("g: increase write seed.\r\n");
                app_sdcard_write_seed++;
                printf("app_sdcard_write_seed = %u\r\n", (unsigned)app_sdcard_write_seed);
                break;

            case 'h':
                printf("h: decrease write seed.\r\n");
                app_sdcard_write_seed--;
                printf("app_sdcard_write_seed = %u\r\n", (unsigned)app_sdcard_write_seed);
                break;

            default:
                printf("\r\n");
            
                printf("a: sdcard_read_single_block().\r\n");
                printf("b: sdcard_read_multi_blocks().\r\n");
                printf("c: sdcard_write_single_block().\r\n");
                printf("d: sdcard_write_multi_blocks().\r\n");
                printf("e: sdcard_init().\r\n");
                printf("f: reset the read/write index.\r\n");
                printf("g: increase write seed.\r\n");
                printf("h: decrease write seed.\r\n");
                
                printf("\r\n");
                break;
        }
    }
}


/* EOF. */

