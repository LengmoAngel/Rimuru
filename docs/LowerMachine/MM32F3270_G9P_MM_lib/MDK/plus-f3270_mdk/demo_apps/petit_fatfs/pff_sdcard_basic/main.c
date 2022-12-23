/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "board_init.h"
#include "pffconf.h"
#include "pff.h"

/*
 * Macros.
 */

/*
 * Variables.
 */

FATFS   app_pff_fs;
DIR     app_pff_dir;
FILINFO app_pff_fno;			/* File information object */
FRESULT app_pff_rc;             /* FatFs return value */
//FIL fil;
//const TCHAR fs_drv[] = "1:/";
const char app_pff_filname[] = "pff.txt";
//BYTE work[FF_MAX_SS]; /* Work area (larger is better for processing time) */
//UINT bw, br;
#define APP_PFF_FIL_BUFF_LEN 32u
//uint8_t fil_write_buff[FIL_BUFF_LEN];
uint8_t app_pff_fil_read_buff[APP_PFF_FIL_BUFF_LEN];
uint32_t app_pff_fil_bw;

//FRESULT fs_ret;
//uint8_t fil_write_seed = 0u;

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

    printf("\r\npetit_fatfs_basic.\r\n");
    
    while (1)
    {
        c = getchar();
        switch (c)
        {

            case 'a':
                printf("pf_mount().\r\n");
                app_pff_rc = pf_mount(&app_pff_fs);
                if( app_pff_rc )
                {
                    printf("fail. %d\r\n", app_pff_rc);
                }
                printf("done.\r\n\r\n");
                
                break;

            case 'b':
                printf("pf_opendir() & pf_readdir().\r\n");
                app_pff_rc = pf_opendir(&app_pff_dir, "");
                if ( app_pff_rc )
                {
                    printf("fail. %d\r\n", app_pff_rc);
                }
                
                while (1)
                {
                    app_pff_rc = pf_readdir(&app_pff_dir, &app_pff_fno);	/* Read a directory item */
                    if ( app_pff_rc || !app_pff_fno.fname[0] )
                    {
                        break;	/* Error or end of dir */
                    }
                    if (app_pff_fno.fattrib & AM_DIR)
                    {
                        printf("   <dir>  %s\r\n", app_pff_fno.fname);
                    }
                    else
                    {
                        printf("%8u  %s\r\n", (unsigned)app_pff_fno.fsize, app_pff_fno.fname);
                    }
                }
                if (app_pff_rc)
                {
                    printf("fail. %d\r\n", app_pff_rc);
                }
                
                printf("done.\r\n\r\n");
                
                break;

            case 'c':
                printf("pf_open() & pf_write().\r\n");
                
                printf("pf_open()\r\n");
                app_pff_rc = pf_open(app_pff_filname);
                if (app_pff_rc)
                {
                    printf("fail. %d\r\n", app_pff_rc);
                    break;
                }
                
                printf("pf_lseek().\r\n");
                app_pff_rc = pf_lseek(0u);
                if (app_pff_rc)
                {
                    printf("fail. %d\r\n", app_pff_rc);
                    break;
                }
                
                /* start write data. */
                printf("pf_write().\r\n");
                uint32_t app_pff_fil_bw;
                app_pff_rc = pf_write("012345678\r\n", 12, (UINT *)&app_pff_fil_bw);
                if ( app_pff_rc || !app_pff_fil_bw )
                {
                    printf("fail. %d\r\n", app_pff_rc);
                    printf("bw: %u\r\n", (unsigned)app_pff_fil_bw);
                    //break;
                }
                
                /* finalize the write process. */
                app_pff_rc = pf_write(0u, 0u, (UINT *)&app_pff_fil_bw);
                if (app_pff_rc)
                {
                    printf("fail. %d\r\n", app_pff_rc);
                    break;
                }
                
                printf("done.\r\n\r\n");
            
                break;
                
            case 'd':
                printf("pf_open() & pf_read().\r\n");
            
                printf("pf_open().\r\n");
                app_pff_rc = pf_open(app_pff_filname);
                if (app_pff_rc)
                {
                    printf("fail. %d\r\n", app_pff_rc);
                    break;
                }
                
                printf("pf_read().\r\n");
                uint32_t br;
                app_pff_rc = pf_read(app_pff_fil_read_buff, sizeof(app_pff_fil_read_buff), (UINT *)&br);
                if (app_pff_rc)
                {
                    printf("fail. %d\r\n", app_pff_rc);
                    break;
                }
                for (uint32_t i = 0u; i < br; i++)
                {
                    printf("%c", app_pff_fil_read_buff[i]);
                }
                printf("\r\n");
            
                printf("done.\r\n\r\n");
                break;
                
                
#if 0
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
#endif
            default: /* help. */
                printf("\r\n");

                printf("a: f_mount().\r\n");
                printf("b: pf_opendir() & pf_readdir().\r\n");
                printf("c: pf_open() & pf_write().\r\n");
                printf("d: pf_open() & pf_read().\r\n");

                printf("\r\n");
                break;
                
        }
    }
}

/* EOF. */

