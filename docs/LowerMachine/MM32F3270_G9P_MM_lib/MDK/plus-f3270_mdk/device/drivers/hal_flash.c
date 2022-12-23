/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "hal_flash.h"

#define FLASH_UNLOCK_KEY0 0x45670123
#define FLASH_UNLOCK_KEY1 0xCDEF89AB

void FLASH_SetLatency(FLASH_Type *FLASHx, FLASH_Latency_Type opt)
{
    FLASHx->ACR = (FLASHx->ACR & ~FLASH_ACR_LATENCY_MASK) | FLASH_ACR_LATENCY(opt);
}

void FLASH_EnablePrefetch(FLASH_Type *FLASHx, bool enable)
{
    if (enable)
    {
        FLASHx->ACR |= FLASH_ACR_PRFTBE_MASK;
        while (0u == (FLASHx->ACR & FLASH_ACR_PRFTBS_MASK))
        {
        }
    }
    else
    {
        FLASHx->ACR &= ~FLASH_ACR_PRFTBE_MASK;
        while (0u != (FLASHx->ACR & FLASH_ACR_PRFTBS_MASK))
        {
        }
    }
}

void FLASH_Unlock(FLASH_Type * FLASHx)
{
    FLASHx->KEYR = FLASH_UNLOCK_KEY0;
    FLASHx->KEYR = FLASH_UNLOCK_KEY1;
}

void FLASH_Lock(FLASH_Type * FLASHx)
{
    FLASHx->CR |= FLASH_CR_LOCK_MASK;
}

void FLASH_UnlockOptionBytes(FLASH_Type * FLASHx)
{
    FLASHx->OPTKEYR = FLASH_UNLOCK_KEY0;
    FLASHx->OPTKEYR = FLASH_UNLOCK_KEY1;
}

void FLASH_LockOptionBytes(FLASH_Type * FLASHx)
{
    FLASHx->CR &= ~FLASH_CR_OPTWRE_MASK; /* disable the "write enable" bit. */
}

uint32_t FLASH_GetStatus(FLASH_Type * FLASHx)
{
    return FLASHx->SR;
}

bool FLASH_WaitDone(FLASH_Type * FLASHx, uint32_t timeout)
{
    bool is_done = false;
    while (timeout > 0u)
    {
        if (0u == (FLASH_STATUS_BUSY & FLASH_GetStatus(FLASHx)) )
        {
            is_done = true;
            break;
        }
        timeout--;
    }
    return is_done;
}

void FLASH_ClearStatus(FLASH_Type * FLASHx, uint32_t flags)
{
    FLASHx->SR = flags;
}

void FLASH_SetCmd(FLASH_Type * FLASHx, uint32_t cmd)
{
    FLASHx->CR |= cmd;
}

void FLASH_ClearCmd(FLASH_Type * FLASHx)
{
    FLASHx->CR &= ~FLASH_CMD_ALL;
}

void FLASH_SetAddr(FLASH_Type * FLASHx, uint32_t addr)
{
    FLASHx->AR = addr;
}

void FLASH_SetData16b(uint32_t addr, uint16_t val)
{
    *((volatile uint16_t *)addr) = val;
}

/* EOF. */

