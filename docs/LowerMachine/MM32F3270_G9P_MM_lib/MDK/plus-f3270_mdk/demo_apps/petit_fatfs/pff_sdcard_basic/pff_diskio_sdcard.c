/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "diskio.h"

#include "board_init.h"
#include "sdcard_sdio.h"

sdcard_t pff_sdcard;






/*-----------------------------------------------------------------------*/
/* Initialize Disk Drive                                                 */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (void)
{
	DSTATUS stat;

	// Put your code here
    if ( sdcard_init(&pff_sdcard, BOARD_SDCARD_SDIO_PORT) )
    {
        stat = RES_OK;
    }
    else
    {
        stat = STA_NOINIT;
    }

	return stat;
}



/*-----------------------------------------------------------------------*/
/* Read Partial Sector                                                   */
/*-----------------------------------------------------------------------*/

uint32_t  pff_sdcard_read_buff_raw[SDCARD_BLOCK_SIZE / 4u];
uint8_t * pff_sdcard_read_buff = (uint8_t *)pff_sdcard_read_buff_raw;
uint32_t  pff_sdcard_read_sector0 = (uint32_t)(-1); /* the most recent reading sector. */

DRESULT disk_readp (
	BYTE* buff,		/* Pointer to the destination object */
	DWORD sector,	/* Sector number (LBA) */
	UINT offset,	/* Offset in the sector */
	UINT count		/* Byte count (bit15:destination) */
)
{
	DRESULT res = RES_OK;

	// Put your code here
    
    if (buff)
    {
        if ( sector != pff_sdcard_read_sector0)
        {
            if ( !sdcard_read_single_block(&pff_sdcard, sector, pff_sdcard_read_buff) )
            {
                return RES_ERROR;
            }
            pff_sdcard_read_sector0 = sector;
        }
        memcpy(buff, pff_sdcard_read_buff + offset, count);
    }

	return res;
}


/*-----------------------------------------------------------------------*/
/* Write Partial Sector                                                  */
/*-----------------------------------------------------------------------*/

uint32_t  pff_sdcard_write_buff_raw[SDCARD_BLOCK_SIZE / 4u];
uint8_t * pff_sdcard_write_buff = (uint8_t *)pff_sdcard_write_buff_raw;
uint32_t  pff_sdcard_write_index = 0u;
uint32_t  pff_sdcard_write_sector;

DRESULT disk_writep (
	const BYTE* buff,		/* Pointer to the data to be written, NULL:Initiate/Finalize write operation */
	DWORD sc		/* Sector number (LBA) or Number of bytes to send */
)
{
	DRESULT res = RES_OK;

	if (!buff)
    {
		if (sc) /* sc means the sector number. */
        {
			// Initiate write process
            pff_sdcard_write_sector = sc;
            pff_sdcard_write_index = 0u;
            memset(pff_sdcard_write_buff, 0u, SDCARD_BLOCK_SIZE);
		}
        else /* execute the most recent write process. */
        {
			// Finalize write process
            if ( !sdcard_write_single_block(&pff_sdcard, pff_sdcard_write_sector, pff_sdcard_write_buff) )
            {
                return RES_ERROR;
            }
		}
	}
    else /* collect the data into write buff. */
    {
		// Send data to the disk
        memcpy(pff_sdcard_write_buff+pff_sdcard_write_index, buff, sc);
        pff_sdcard_write_index += sc;
        if (pff_sdcard_write_index >= SDCARD_BLOCK_SIZE )
        {
            return RES_PARERR;
        }
	}

	return res;
}

/* EOF. */

