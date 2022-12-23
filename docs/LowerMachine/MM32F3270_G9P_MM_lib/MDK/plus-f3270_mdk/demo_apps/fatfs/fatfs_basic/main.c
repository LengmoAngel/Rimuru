/*
 * Copyright 2022 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board_init.h"
#include "ffconf.h"
#include "ff.h"

/*
 * Macros.
 */

/*
 * Variables.
 */

FATFS fs;
FIL fil;
const TCHAR fs_drv[] = "1:/";
const TCHAR filname[] = "1:/hello.txt";
BYTE work[FF_MAX_SS]; /* Work area (larger is better for processing time) */
UINT bw, br;
#define FIL_BUFF_LEN 16u
uint8_t fil_write_buff[FIL_BUFF_LEN];
uint8_t fil_read_buff[FIL_BUFF_LEN];

FRESULT fs_ret;

uint8_t fil_write_seed = 0u;

/*
 * Declerations.
 */

/*
 * Functions.
 */
int main(void)
{
    uint8_t c;

    BOARD_Init();

    printf("fatfs_basic\r\n");
    printf("Press any key for help...\r\n");

    while (1)
    {
        c = getchar();
        switch (c)
        {
            case 'a':
                printf("a: f_mkfs().\r\n");

                if ( !f_mkfs(fs_drv, 0u, work, sizeof(work)) )
                {
                    printf("succ.\r\n");
                }
                else
                {
                    printf("fail.\r\n");
                }
                break;

            case 'b':
                printf("b: f_mount().\r\n");
                if( !f_mount(&fs, fs_drv ,1) )
                {
                    printf("succ.\r\n");
                }
                else
                {
                    printf("fail.\r\n");
                }
                break;

            case 'c':
                printf("c: f_open() & f_write() & f_close().\r\n");

                printf("f_open().\r\n");
                fs_ret = f_open(&fil, filname, FA_CREATE_NEW | FA_WRITE );
                if ( fs_ret != FR_OK )
                {
                    printf("fail.\r\n");
                    break;
                }

                printf("f_write().\r\n");

                sprintf((char *)fil_write_buff, "hi, %d\r\n", fil_write_seed++), 

                fs_ret = f_write(&fil, fil_write_buff, FIL_BUFF_LEN, &bw);
                if (bw != FIL_BUFF_LEN)
                {
                    printf("fail.\r\n");

                    f_close(&fil);
                    break;
                }

                printf("f_close().\r\n");
                f_close(&fil);

                printf("succ.\r\n");

                break;

            case 'd':
                printf("d: f_open() & f_read() & f_close().\r\n");

                printf("f_open().\r\n");
                fs_ret = f_open(&fil, filname, FA_READ );
                if ( fs_ret != FR_OK )
                {
                    printf("fail.\r\n");
                    break;
                }

                printf("f_read()\r\n");
                fs_ret = f_read(&fil, fil_read_buff, FIL_BUFF_LEN, &br);
                if (br != FIL_BUFF_LEN)
                {
                    printf("fail.\r\n");

                    f_close(&fil);
                    break;
                }

                for (uint32_t i  = 0u; i < FIL_BUFF_LEN; i++)
                {
                    printf("%c", fil_read_buff[i]);
                }
                printf("\r\n");

                printf("f_close().\r\n");
                f_close(&fil);

                printf("succ.\r\n");

                break;

            case 'f':
                printf("f: f_unlink().\r\n");

                f_unlink(filname);

                printf("file removed.\r\n");

                break;

            default: /* help. */
                printf("\r\n");

                printf("a: f_mkfs().\r\n");
                printf("b: f_mount().\r\n");
                printf("c: f_open() & f_write() & f_close().\r\n");
                printf("d: f_open() & f_read() & f_close().\r\n");
                printf("f: f_unlink().\r\n");

                printf("\r\n");
                break;
        }
    }
}

/* EOF. */
