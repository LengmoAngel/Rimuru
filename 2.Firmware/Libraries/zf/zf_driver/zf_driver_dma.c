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
* 文件名称          zf_driver_dma
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

#include "hal_device_registers.h"
#include "zf_common_interrupt.h"

#include "zf_driver_dma.h"

static DMA_Type *dma_index[2] = {DMA1, DMA2};

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     dma 传输数据数量设置
// 参数说明     ch              选择 dma 通道 (详见 zf_driver_dma.h 中枚举 dma_channel_enum 定义)
// 参数说明     size            传输数据数量
// 返回参数     void
// 使用示例     dma_set_count(MT9V03X_DMA_CH, image_size);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void dma_set_count (dma_channel_enum ch, const uint16 transfer_count)
{
    dma_index[(ch & 0xF0) >> 4]->CH[ch & 0x0f].CNDTR = transfer_count;          // 传输数量
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     dma 传输使能
// 参数说明     ch              选择 dma 通道 (详见 zf_driver_dma.h 中枚举 dma_channel_enum 定义)
// 返回参数     void
// 使用示例     dma_enable(MT9V03X_DMA_CH);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void dma_enable (dma_channel_enum ch)
{
    dma_index[(ch & 0xF0) >> 4]->CH[ch & 0x0f].CCR |= 0x00000001;               // 使能 DMA
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     dma 传输禁止
// 参数说明     ch              选择 dma 通道 (详见 zf_driver_dma.h 中枚举 dma_channel_enum 定义)
// 返回参数     void
// 使用示例     dma_disable(MT9V03X_DMA_CH);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void dma_disable (dma_channel_enum ch)
{
    dma_index[(ch & 0xF0) >> 4]->CH[ch & 0x0f].CCR &= 0xFFFFFFFE;               // 禁止 DMA
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     dma 初始化 摄像头接口
// 参数说明     ch              选择 dma 通道 (详见 zf_driver_dma.h 中枚举 dma_channel_enum 定义)
// 参数说明     size            传输数据数量
// 参数说明     peripheral_add  外设地址 摄像头数据接口的地址
// 参数说明     memory_add      摄像头数据存放地址
// 返回参数     void
// 使用示例     dma_camera_init(MT9V03X_DMA_CH, image_size, (uint32)MT9V03X_DATA_ADD, (uint32)camera_buffer_addr);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void dma_camera_init (dma_channel_enum ch, const uint32 size, const uint32 peripheral_add, const uint32 memory_add)
{
    RCC->AHB1ENR |= (0x00200000 << ((ch & 0xF0) >> 4));                         // 使能 DMA 时钟
    RCC->AHB1RSTR |= (0x00200000 << ((ch & 0xF0) >> 4));                        // 复位 DMA 外设
    RCC->AHB1RSTR &= ~(0x00200000 << ((ch & 0xF0) >> 4));                       // 复位 结束

    dma_index[(ch & 0xF0) >> 4]->CH[ch & 0x0f].CNDTR = size;                    // 传输数量
    dma_index[(ch & 0xF0) >> 4]->CH[ch & 0x0f].CPAR = peripheral_add;           // 外设地址
    dma_index[(ch & 0xF0) >> 4]->CH[ch & 0x0f].CMAR = memory_add;               //  
    dma_index[(ch & 0xF0) >> 4]->CH[ch & 0x0f].CCR = 0x0000B082;                // 设置 自动重装载 最高优先级 存储器地址递增 使能传输完成中断 使能 DMA

    switch(ch)
    {
        case DMA1_CHANNEL1: interrupt_enable(DMA1_CH1_IRQn);    break;
        case DMA1_CHANNEL2: interrupt_enable(DMA1_CH2_IRQn);    break;
        case DMA1_CHANNEL3: interrupt_enable(DMA1_CH3_IRQn);    break;
        case DMA1_CHANNEL4: interrupt_enable(DMA1_CH4_IRQn);    break;
        case DMA1_CHANNEL5: interrupt_enable(DMA1_CH5_IRQn);    break;
        case DMA1_CHANNEL6: interrupt_enable(DMA1_CH6_IRQn);    break;
        case DMA1_CHANNEL7: interrupt_enable(DMA1_CH7_IRQn);    break;

        case DMA2_CHANNEL1: interrupt_enable(DMA2_CH1_IRQn);    break;
        case DMA2_CHANNEL2: interrupt_enable(DMA2_CH2_IRQn);    break;
        case DMA2_CHANNEL3: interrupt_enable(DMA2_CH3_IRQn);    break;
        case DMA2_CHANNEL4: interrupt_enable(DMA2_CH4_IRQn);    break;
        case DMA2_CHANNEL5: interrupt_enable(DMA2_CH5_IRQn);    break;
    }
}
