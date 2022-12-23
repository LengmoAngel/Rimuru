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
* 文件名称          zf_driver_iic
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

#ifndef _zf_driver_iic_h_
#define _zf_driver_iic_h_

#include "zf_common_typedef.h"

typedef enum                                                                    // 枚举串口引脚 此枚举定义不允许用户修改
{
// IIC 1 引脚 SCL
    IIC1_SCL_A9         = 0x0409,                                               // 0x 0[IIC1] 4[AF4] 09[A9]
    IIC1_SCL_A15        = 0x040F,                                               // 0x 0[IIC1] 4[AF4] 0F[A15]
    IIC1_SCL_B6         = 0x0426,                                               // 0x 0[IIC1] 4[AF4] 26[B6]
    IIC1_SCL_B8         = 0x0428,                                               // 0x 0[IIC1] 4[AF4] 28[B8]
    IIC1_SCL_C0         = 0x0440,                                               // 0x 0[IIC1] 4[AF4] 40[C0]
    IIC1_SCL_C6         = 0x0446,                                               // 0x 0[IIC1] 4[AF4] 46[C6]
    IIC1_SCL_D10        = 0x046A,                                               // 0x 0[IIC1] 4[AF4] 6A[D10]

// IIC 2 引脚 SCL
    IIC2_SCL_B10        = 0x142A,                                               // 0x 1[IIC2] 4[AF4] 2A[B10]
    IIC2_SCL_C2         = 0x1442,                                               // 0x 1[IIC2] 4[AF4] 42[C2]
    IIC2_SCL_C8         = 0x1448,                                               // 0x 1[IIC2] 4[AF4] 48[C8]
    IIC2_SCL_E5         = 0x1485,                                               // 0x 1[IIC2] 4[AF4] 85[E5]
}iic_scl_pin_enum;

typedef enum                                                                    // 枚举串口引脚 此枚举定义不允许用户修改
{
// IIC 1 引脚 SDA
    IIC1_SDA_A10        = 0x040A,                                               // 0x 0[IIC1] 4[AF4] 0A[A10]
    IIC1_SDA_A14        = 0x040E,                                               // 0x 0[IIC1] 4[AF4] 0E[A14]
    IIC1_SDA_B7         = 0x0427,                                               // 0x 0[IIC1] 4[AF4] 27[B7]
    IIC1_SDA_B9         = 0x0429,                                               // 0x 0[IIC1] 4[AF4] 29[B9]
    IIC1_SDA_C1         = 0x0441,                                               // 0x 0[IIC1] 4[AF4] 41[C1]
    IIC1_SDA_C7         = 0x0447,                                               // 0x 0[IIC1] 4[AF4] 47[C7]
    IIC1_SDA_D11        = 0x046B,                                               // 0x 0[IIC1] 4[AF4] 6B[D11]

// IIC 2 引脚 SDA
    IIC2_SDA_B11        = 0x142B,                                               // 0x 1[IIC2] 4[AF4] 2B[B11]
    IIC2_SDA_C3         = 0x1443,                                               // 0x 1[IIC2] 4[AF4] 43[C3]
    IIC2_SDA_C9         = 0x1449,                                               // 0x 1[IIC2] 4[AF4] 49[C9]
    IIC2_SDA_E6         = 0x1486,                                               // 0x 1[IIC2] 4[AF4] 86[E6]
}iic_sda_pin_enum;

typedef enum                                                                    // 枚举 IIC 工作状态 此枚举定义不允许用户修改
{
    IIC_SUCCESS,
    IIC_WRITE_TIMEOUT,
    IIC_READ_TIMEOUT,
}iic_state_enum;

typedef enum                                                                    // 枚举 IIC 编号 此枚举定义不允许用户修改
{
    IIC_1,
    IIC_2,
}iic_index_enum;

void        iic_write_8bit              (iic_index_enum iic_n, uint8 target_addr, const uint8 data);
void        iic_write_8bit_array        (iic_index_enum iic_n, uint8 target_addr, const uint8 *data, uint32 len);

void        iic_write_16bit             (iic_index_enum iic_n, uint8 target_addr, const uint16 data);
void        iic_write_16bit_array       (iic_index_enum iic_n, uint8 target_addr, const uint16 *data, uint32 len);

void        iic_write_8bit_register     (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name, const uint8 data);
void        iic_write_8bit_registers    (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name, const uint8 *data, uint32 len);

void        iic_write_16bit_register    (iic_index_enum iic_n, uint8 target_addr, const uint16 register_name, const uint16 data);
void        iic_write_16bit_registers   (iic_index_enum iic_n, uint8 target_addr, const uint16 register_name, const uint16 *data, uint32 len);

uint8       iic_read_8bit               (iic_index_enum iic_n, uint8 target_addr);
void        iic_read_8bit_array         (iic_index_enum iic_n, uint8 target_addr, uint8 *data, uint32 len);

uint16      iic_read_16bit              (iic_index_enum iic_n, uint8 target_addr);
void        iic_read_16bit_array        (iic_index_enum iic_n, uint8 target_addr, uint16 *data, uint32 len);

uint8       iic_read_8bit_register      (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name);
void        iic_read_8bit_registers     (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name, uint8 *data, uint32 len);

uint16      iic_read_16bit_register     (iic_index_enum iic_n, uint8 target_addr, const uint16 register_name);
void        iic_read_16bit_registers    (iic_index_enum iic_n, uint8 target_addr, const uint16 register_name, uint16 *data, uint32 len);

void        iic_transfer_8bit_array     (iic_index_enum iic_n, uint8 target_addr, const uint8 *write_data, uint32 write_len, uint8 *read_data, uint32 read_len);
void        iic_transfer_16bit_array    (iic_index_enum iic_n, uint8 target_addr, const uint16 *write_data, uint32 write_len, uint16 *read_data, uint32 read_len);

void        iic_sccb_write_register     (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name, uint8 data);
uint8       iic_sccb_read_register      (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name);

void        iic_init                    (iic_index_enum iic_n, uint8 addr, uint32 speed, iic_scl_pin_enum scl_pin, iic_sda_pin_enum sda_pin);

#ifdef COMPATIBLE_WITH_OLDER_VERSIONS                                           // 兼容旧版本开源库接口名称

#endif

#endif
