/*********************************************************************************************************************
* MM32F327X-G9P Opensourec Library 即（MM32F327X-G9P 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
* 
* 本文件是 MM32F327X-G9P 开源库的一部分
* 
* MM32F327X-G9P 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
* 
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
* 
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
* 
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
* 
* 文件名称          zf_driver_sdio
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          IAR 8.32.4 or MDK 5.37
* 适用平台          MM32F327X_G9P
* 店铺链接          https://seekfree.taobao.com/
* 
* 修改记录
* 日期              作者                备注
* 2022-08-10        Teternal            first version
********************************************************************************************************************/

#ifndef _zf_driver_sdio_h_
#define _zf_driver_sdio_h_

#include "hal_device_registers.h"
#include "zf_common_typedef.h"

#define SDIO_TIMEOUT_COUNT          (100)

typedef enum                                                                    // 枚举 SDIO 工作状态 此枚举定义不允许用户修改
{
    SDIO_ERROR_STATE_NO_ERROR,
    SDIO_ERROR_STATE_TIME_OUT,
}sdio_error_state_enum;

typedef enum                                                                    // 枚举 SDIO 数据总线位宽   此枚举定义不允许用户修改
{
    SDIO_DATA_BUS_1BIT,                                                         // 1bit 数据总线位宽
    SDIO_DATA_BUS_4BIT,                                                         // 4bit 数据总线位宽
}sdio_data_bus_width_enum;

typedef enum                                                                    // SD 卡响应信息类型 此结构体定义不允许用户修改
{
    SDIO_RESP_TYPE_R1,                                                          // 32 bit + 8 bit CRC
    SDIO_RESP_TYPE_R2,                                                          // 128 bit + 8 bit CRC, for CID and CSD
    SDIO_RESP_TYPE_R3,                                                          // 32 bit + 8 bit CRC, for OCR
    SDIO_RESP_TYPE_R6,                                                          // 32 bit + 8 bit CRC, for RCA
    SDIO_RESP_TYPE_R7,                                                          // 32 bit + 8 bit CRC, for card interface condition
}sdio_resp_type_enum;

#define sdio_switch_fifo_dir(x)             ((x) ? (SDIO->BUFCTL |= 0x00000800) : (SDIO->BUFCTL &= 0xFFFFF7FF))
#define sdio_switch_fifo_read_wait(x)       ((x) ? (SDIO->MMCCTRL |= 0x00000400) : (SDIO->MMCCTRL &= 0xFFFFFBFF))
#define sdio_clear_fifo()                   (SDIO->BUFCTL |= 0x00008000)
#define sdio_set_block_count(x)             (SDIO->MMCBLOCKCNT = (x))

#define sdio_set_fifo_data(x)               (SDIO->DATABUF[0] = (x))
#define sdio_get_fifo_data()                (SDIO->DATABUF[0])

uint32                  sdio_get_state              (void);
void                    sdio_clear_state            (uint32 flags);
sdio_error_state_enum   sdio_execute_cmd            (uint8 cmd_index, uint32 param, uint32 flags);
void                    sdio_execute_data           (uint32 data);
sdio_error_state_enum   sdio_request_resp           (sdio_resp_type_enum type, uint32 *resp);

void                    sdio_set_data_bus_width     (sdio_data_bus_width_enum width);
void                    sdio_disable                (void);
void                    sdio_enable                 (void);
void                    sdio_init                   (void);

#endif
