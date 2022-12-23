/*
 * Copyright 2022 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __HAL_FLASH_H__
#define __HAL_FLASH_H__

#include "hal_common.h"

/*!
 * @addtogroup FLASH
 * @{
 */

/*!
 * @brief FLASH driver version number.
 */
#define FLASH_DRIVER_VERSION 0u /*!< flash_0. */

/*!
 * @brief FLASH page size.
 */
#define FLASH_PAGE_SIZE    0x400 /*!< 1K Bytes. */

/*!
 * @addtogroup FLASH_STATUS
 * @{
 */
#define FLASH_STATUS_BUSY                 FLASH_SR_BSY_MASK      /*!< Status flag when FLASH is busy. */
#define FLASH_STATUS_PROGRAM_ERR          FLASH_SR_PGERR_MASK    /*!< Status flag when FLASH is program error. */
#define FLASH_STATUS_WRITE_PROTECTION_ERR FLASH_SR_WRPRTERR_MASK /*!< Status flag when FLASH is write protection error. */
#define FLASH_STATUS_END_OF_OPERATION     FLASH_SR_EOP_MASK      /*!< Status flag when FLASH is end of operation. */

/*!
 * @addtogroup FLASH_CMD
 * @{
 */
#define FLASH_CMD_PROGRAM     FLASH_CR_PG_MASK    /*!< FLASH program command. */
#define FLASH_CMD_PROGRAM_OPT FLASH_CR_OPTPG_MASK /*!< FLASH option byte program command. */
#define FLASH_CMD_ERASE_PAGE  FLASH_CR_PER_MASK   /*!< FLASH erase page command. */
#define FLASH_CMD_ERASE_MASS  FLASH_CR_MER_MASK   /*!< FLASH erase mass command. */
#define FLASH_CMD_ERASE_OPT   FLASH_CR_OPTER_MASK /*!< FLASH erase option byte command. */
#define FLASH_CMD_START_ERASE FLASH_CR_STRT_MASK  /*!< FLASH start erase command. */
#define FLASH_CMD_ALL ( FLASH_CMD_PROGRAM \
                      | FLASH_CMD_ERASE_PAGE \
                      | FLASH_CMD_ERASE_MASS \
                      | FLASH_CMD_PROGRAM_OPT \
                      | FLASH_CMD_ERASE_OPT \
                      | FLASH_CMD_START_ERASE )  /*!< FLASH all command. */

/*!
 * @brief FLASH latency type.
 */
typedef enum
{
    FLASH_Latency_0_Cycle = 0u, /*!< for 0 < SYSCLK ≤ 24MHz. */
    FLASH_Latency_1_Cycle = 1u, /*!< 24MHz < SYSCLK ≤ 48MHz. */
    FLASH_Latency_2_Cycle = 2u, /*!< 48MHz < SYSCLK ≤ 72MHz. */
    FLASH_Latency_3_Cycle = 3u, /*!< 72MHz < SYSCLK ≤ 96MHz. */
    FLASH_Latency_4_Cycle = 4u, /*!< 96MHz < SYSCLK ≤ 120MHz. */
} FLASH_Latency_Type;

/*!
 * @brief Set the FLASH latency.
 *
 * @param FLASHx FLASH instance.
 * @param opt FLSH latency type. See to @ref FLASH_Latency_Type.
 * @return None.
 */
void FLASH_SetLatency(FLASH_Type *FLASHx, FLASH_Latency_Type opt);

/*!
 * @brief Enable the prefetch buffer.
 *
 * @param FLASHx FLASH instance.
 * @param enable 'true' to enable the prefetch buffer, 'false' to disable the prefetch buffer.
 * @return None.
 */
void FLASH_EnablePrefetch(FLASH_Type *FLASHx, bool enable);

/*!
 * @brief Unlock the FLASH module.
 *
 * @param FLASHx FLASH instance.
 * @return None.
 */
void FLASH_Unlock(FLASH_Type * FLASHx);

/*!
 * @brief Lock the FLASH module.
 *
 * @param FLASHx FLASH instance.
 * @return None.
 */
void FLASH_Lock(FLASH_Type * FLASHx);

/*!
 * @brief Unlock the FLASH option bytes.
 *
 * @param FLASHx FLASH instance.
 * @return None.
 */
void FLASH_UnlockOptionBytes(FLASH_Type * FLASHx);

/*!
 * @brief Unlock the FLASH option bytes.
 *
 * @param FLASHx FLASH instance.
 * @return None.
 */
void FLASH_LockOptionBytes(FLASH_Type * FLASHx);

/*!
 * @brief Get the current status flags of the FLASH module.
 *
 * @param FLASHx FLASH instance.
 * @return Status flags. See to @ref FLASH_STATUS.
 */
uint32_t FLASH_GetStatus(FLASH_Type * FLASHx);

/*!
 * @brief Clear the status flags of the FLASH module.
 *
 * @param FLASHx FLASH instance.
 * @param flags The mask codes of the indicated flags to be cleared.
 * @return None.
 */
void FLASH_ClearStatus(FLASH_Type * FLASHx, uint32_t flags);

/*!
 * @brief Wait for the FLASH operate done.
 *
 * @param FLASHx FLASH instance.
 * @param timeout The time limit for wait the FLASH operate done.
 * @return 'true' to FLASH operate succeed, 'false' to operate failed.
 */
bool FLASH_WaitDone(FLASH_Type * FLASHx, uint32_t timeout);

/*!
 * @brief Set the current status of the FLASH module.
 *
 * @param FLASHx FLASH instance.
 * @param cmd The command to be set. See to @ref FLASH_CMD.
 * @return None.
 */
void FLASH_SetCmd(FLASH_Type * FLASHx, uint32_t cmd);

/*!
 * @brief Clear all set command in the FLASH module.
 *
 * @param FLASHx FLASH instance.
 * @return None.
 */
void FLASH_ClearCmd(FLASH_Type * FLASHx);

/*!
 * @brief Set the flash address.
 *
 * @param FLASHx FLASH instance.
 * @param addr The address to be set.
 * @return None.
 */
void FLASH_SetAddr(FLASH_Type * FLASHx, uint32_t addr);

/*!
 * @brief Set the 16 bit data to specified address.
 *
 * @param addr The address to be set.
 * @param value The value to be set.
 * @return None.
 */
void FLASH_SetData16b(uint32_t addr, uint16_t value);

/*!
 *@}
 */

#endif /* __HAL_FLASH_H__ */
