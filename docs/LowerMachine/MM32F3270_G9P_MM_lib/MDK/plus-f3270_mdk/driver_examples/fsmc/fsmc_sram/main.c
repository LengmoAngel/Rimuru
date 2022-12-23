/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board_init.h"

/*
 * Macros.
 */

#define SRAM_MEM_START  0u
#define SRAM_MEM_SIZE   (1024 * 512 * 2) /* 512K * 16b. */

/*
 * Variables.
 */

/*
 * Declerations.
 */

void app_sram_init(void);
bool app_sram_8b_test(void);
bool app_sram_16b_test(void);
bool app_sram_32b_test(void);


/*
 * Functions.
 */
int main(void)
{
    BOARD_Init();

    printf("fsmc sram example.\r\n");

    app_sram_init();

    while (1)
    {
        getchar();
        app_sram_8b_test();
        app_sram_16b_test();
        app_sram_32b_test();
    }
}

void app_sram_init(void)
{
    FSMC_Init_Type fsmc_init =
    {
        .MemType = FSMC_MemType_SRAM,
        .MemSize = FSMC_MemSize_1MB,
    };

    FSMC_Conf_Type fsmc_conf =
    {
        .ReadPeriod    = BOARD_SRAM_FSMC_READ_PERIOD,
        .AddrSetTime   = BOARD_SRAM_FSMC_ADDR_SET_TIME,
        .WriteHoldTime = BOARD_SRAM_FSMC_WHITE_HOLD_TIME,
        .WritePeriod   = BOARD_SRAM_FSMC_WRITE_PERIOD,
        .ReadySignal   = BOARD_SRAM_FSMC_READY_SIGNAL,
        .SMReadPipe    = BOARD_SRAM_FSMC_SM_READ_PIPE,
        .BusWidth      = BOARD_SRAM_FSMC_BUS_WIDTH
    };

    /* init fsmc. */
    FSMC_Init(BOARD_SRAM_FSMC_PORT, BOARD_SRAM_FSMC_BANK_INDEX, &fsmc_init);

    /* fsmc set conf. */
    FSMC_SetConf(BOARD_SRAM_FSMC_PORT, BOARD_SRAM_FSMC_SET_INDEX, &fsmc_conf);
    FSMC_EnableConf(BOARD_SRAM_FSMC_PORT, BOARD_SRAM_FSMC_BANK_INDEX, BOARD_SRAM_FSMC_SET_INDEX);
}

bool app_sram_8b_test(void)
{
    uint32_t err_count = 0u;

    /* write sram. */
    for (uint32_t i = 0u; i < SRAM_MEM_SIZE; i++)
    {
        FSMC_PutData8(BOARD_SRAM_FSMC_PORT, BOARD_SRAM_FSMC_BANK_INDEX, i + SRAM_MEM_START, (i % 256u));
    }

    for (uint32_t i = 0u; i < SRAM_MEM_SIZE; i++)
    {
        if ( (i % 256u) != FSMC_GetData8(BOARD_SRAM_FSMC_PORT, BOARD_SRAM_FSMC_BANK_INDEX, i + SRAM_MEM_START) )
        {
            err_count++;
        }
    }

    if (err_count != 0u)
    {
        printf("sram 8-bit access error: %u\r\n", (unsigned)err_count);
        return false;
    }
    else
    {
        printf("sram 8-bit access succ.\r\n");
        return true;
    }
}

bool app_sram_16b_test(void)
{
    uint32_t err_count = 0u;

    /* write sram. */
    for (uint32_t i = 0u; i < SRAM_MEM_SIZE; i = i + 2)
    {
        FSMC_PutData16(BOARD_SRAM_FSMC_PORT, BOARD_SRAM_FSMC_BANK_INDEX, i + SRAM_MEM_START, (i % 65536u));
    }

    for (uint32_t i = 0u; i < SRAM_MEM_SIZE; i = i + 2)
    {
        if ( (i % 65536u) != FSMC_GetData16(BOARD_SRAM_FSMC_PORT, BOARD_SRAM_FSMC_BANK_INDEX, i + SRAM_MEM_START) )
        {
            err_count++;
        }
    }

    if (err_count != 0u)
    {
        printf("sram 16-bit access error: %u\r\n", (unsigned)err_count);
        return false;
    }
    else
    {
        printf("sram 16-bit access succ.\r\n");
        return true;
    }
}

bool app_sram_32b_test(void)
{
    uint32_t err_count = 0u;

    /* write sram. */
    for (uint32_t i = 0u; i < SRAM_MEM_SIZE; i = i + 4)
    {
        FSMC_PutData32(BOARD_SRAM_FSMC_PORT, BOARD_SRAM_FSMC_BANK_INDEX, i + SRAM_MEM_START, i);
    }

    for (uint32_t i = 0u; i < SRAM_MEM_SIZE; i = i + 4)
    {
        if ( i != FSMC_GetData32(BOARD_SRAM_FSMC_PORT, BOARD_SRAM_FSMC_BANK_INDEX, i + SRAM_MEM_START) )
        {
            err_count++;
        }
    }

    if (err_count != 0u)
    {
        printf("sram 32-bit access error: %u\r\n", (unsigned)err_count);
        return false;
    }
    else
    {
        printf("sram 32-bit access succ.\r\n");
        return true;
    }
}


/* EOF. */
