/*
 * Copyright 2022 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */

#include "sdcard_sdio.h"
#include "board_init.h"

/* Definitions of physical drive number for each drive */
#define DEV_RAM     0   /* Example: Map Ramdisk to physical drive 0 */
#define DEV_MMC     1   /* Example: Map MMC/SD card to physical drive 1 */
#define DEV_USB     2   /* Example: Map USB MSD to physical drive 2 */


sdcard_t fatfs_sdcard;

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
    BYTE pdrv       /* Physical drive nmuber to identify the drive */
)
{
    DSTATUS stat = 0u;
    //int result;

    switch (pdrv) {
    case DEV_RAM :
        //result = RAM_disk_status();

        // translate the reslut code here

        return stat;

    case DEV_MMC :
        //result = MMC_disk_status();
        stat = RES_OK;

        // translate the reslut code here

        return stat;

    case DEV_USB :
        //result = USB_disk_status();

        // translate the reslut code here

        return stat;
    }
    return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
    BYTE pdrv               /* Physical drive nmuber to identify the drive */
)
{
    DSTATUS stat = 0u;
    //int result;

    switch (pdrv) {
    case DEV_RAM :
        //result = RAM_disk_initialize();

        // translate the reslut code here

        return stat;

    case DEV_MMC :
        //result = MMC_disk_initialize();
        if ( sdcard_init(&fatfs_sdcard, BOARD_SDCARD_SDIO_PORT) )
        {
            stat = RES_OK;
        }
        else
        {
            stat = STA_NOINIT;
        }

        // translate the reslut code here

        return stat;

    case DEV_USB :
        //result = USB_disk_initialize();

        // translate the reslut code here

        return stat;
    }
    return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
    BYTE pdrv,      /* Physical drive nmuber to identify the drive */
    BYTE *buff,     /* Data buffer to store read data */
    LBA_t sector,   /* Start sector in LBA */
    UINT count      /* Number of sectors to read */
)
{
    DRESULT res = 0u;
    //int result;

    switch (pdrv) {
    case DEV_RAM :
        // translate the arguments here

        //result = RAM_disk_read(buff, sector, count);

        // translate the reslut code here

        return res;

    case DEV_MMC :
        // translate the arguments here

        //result = MMC_disk_read(buff, sector, count);

        if ( sdcard_read_multi_blocks(&fatfs_sdcard, sector, count, buff) )
        {
            res = RES_OK;
        }
        else
        {
            res= RES_ERROR;
        }

        // translate the reslut code here

        return res;

    case DEV_USB :
        // translate the arguments here

        //result = USB_disk_read(buff, sector, count);

        // translate the reslut code here

        return res;
    }

    return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
    BYTE pdrv,          /* Physical drive nmuber to identify the drive */
    const BYTE *buff,   /* Data to be written */
    LBA_t sector,       /* Start sector in LBA */
    UINT count          /* Number of sectors to write */
)
{
    DRESULT res = 0u;
    // int result;

    switch (pdrv) {
    case DEV_RAM :
        // translate the arguments here

        //result = RAM_disk_write(buff, sector, count);

        // translate the reslut code here

        return res;

    case DEV_MMC :
        // translate the arguments here

        //result = MMC_disk_write(buff, sector, count);
        if ( sdcard_write_multi_blocks(&fatfs_sdcard, sector, count, (uint8_t *)buff) )
        {
            res = RES_OK;
        }
        else
        {
            res = RES_ERROR;
        }

        // translate the reslut code here

        return res;

    case DEV_USB :
        // translate the arguments here

        //result = USB_disk_write(buff, sector, count);

        // translate the reslut code here

        return res;
    }

    return RES_PARERR;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
    BYTE pdrv,      /* Physical drive nmuber (0..) */
    BYTE cmd,       /* Control code */
    void *buff      /* Buffer to send/receive control data */
)
{
    DRESULT res = 0u;
    //int result;

    switch (pdrv) {
    case DEV_RAM :

        // Process of the command for the RAM drive

        return res;

    case DEV_MMC :

        // Process of the command for the MMC/SD card
        switch (cmd)
        {
            case GET_SECTOR_COUNT:
                *(DWORD *)buff = fatfs_sdcard.block_cnt;
                res = RES_OK;
                break;

            case GET_BLOCK_SIZE:
                *(DWORD *)buff = 512u;
                res = RES_OK;
                break;
        }

        return res;

    case DEV_USB :

        // Process of the command the USB drive

        return res;
    }

    return RES_PARERR;
}
/* EOF. */