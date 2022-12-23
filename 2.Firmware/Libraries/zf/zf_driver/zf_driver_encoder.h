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
* 文件名称          zf_driver_encoder
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

#ifndef _zf_driver_encoder_h_
#define _zf_driver_encoder_h_

#include "zf_common_typedef.h"

typedef enum
{
    // Advanced Timer 16 bits TIM1
    TIM1_ENCOEDER_CH1_A8        = 0x0108,                                       // 0x 0[TIM1] 1[AF1] 08[A8]
    TIM1_ENCOEDER_CH1_E9        = 0x0189,                                       // 0x 0[TIM1] 1[AF1] 89[E9]

    // Advanced Timer 16 bits TIM8
    TIM8_ENCOEDER_CH1_C6        = 0x7346,                                       // 0x 7[TIM8] 3[AF3] 46[C6]

    // General Timer 32 bits TIM2
    TIM2_ENCOEDER_CH1_A0        = 0x1100,                                       // 0x 1[TIM2] 1[AF1] 00[A0]
    TIM2_ENCOEDER_CH1_A5        = 0x1105,                                       // 0x 1[TIM2] 1[AF1] 05[A5]
    TIM2_ENCOEDER_CH1_A15       = 0x110F,                                       // 0x 1[TIM2] 1[AF1] 0F[A15]

    // General Timer 32 bits TIM5
    TIM5_ENCOEDER_CH1_A0        = 0x4200,                                       // 0x 4[TIM5] 2[AF2] 00[A0]

    // General Timer 16 bits TIM3
    TIM3_ENCOEDER_CH1_A6        = 0x2206,                                       // 0x 2[TIM3] 2[AF2] 06[A6]
    TIM3_ENCOEDER_CH1_B4        = 0x2224,                                       // 0x 2[TIM3] 2[AF2] 24[B4]
    TIM3_ENCOEDER_CH1_C6        = 0x2246,                                       // 0x 2[TIM3] 2[AF2] 46[C6]

    // General Timer 16 bits TIM4
    TIM4_ENCOEDER_CH1_B6        = 0x3226,                                       // 0x 3[TIM4] 2[AF2] 26[B6]
}encoder_channel1_enum;

typedef enum
{
    // Advanced Timer 16 bits TIM1
    TIM1_ENCOEDER_CH2_A9        = 0x0109,                                       // 0x 0[TIM1] 1[AF1] 09[A9]
    TIM1_ENCOEDER_CH2_E11       = 0x018B,                                       // 0x 0[TIM1] 1[AF1] 8B[E11]

    // Advanced Timer 16 bits TIM8
    TIM8_ENCOEDER_CH2_C7        = 0x7347,                                       // 0x 7[TIM8] 3[AF3] 47[C7]

    // General Timer 32 bits TIM2
    TIM2_ENCOEDER_CH2_A1        = 0x1101,                                       // 0x 1[TIM2] 1[AF1] 01[A1]
    TIM2_ENCOEDER_CH2_B3        = 0x1123,                                       // 0x 1[TIM2] 1[AF1] 23[B3]

    // General Timer 32 bits TIM5
    TIM5_ENCOEDER_CH2_A1        = 0x4201,                                       // 0x 4[TIM5] 2[AF2] 01[A1]

    // General Timer 16 bits TIM3
    TIM3_ENCOEDER_CH2_A7        = 0x2207,                                       // 0x 2[TIM3] 2[AF2] 07[A7]
    TIM3_ENCOEDER_CH2_B5        = 0x2225,                                       // 0x 2[TIM3] 2[AF2] 25[B5]
    TIM3_ENCOEDER_CH2_C7        = 0x2247,                                       // 0x 2[TIM3] 2[AF2] 47[C7]

    // General Timer 16 bits TIM4
    TIM4_ENCOEDER_CH2_B7        = 0x3227,                                       // 0x 3[TIM4] 2[AF2] 27[B7]
    TIM4_ENCOEDER_CH2_D13       = 0x326D,                                       // 0x 3[TIM4] 2[AF2] 6D[D13]
}encoder_channel2_enum;

typedef enum
{
    TIM1_ENCOEDER = 0,
    TIM2_ENCOEDER,
    TIM3_ENCOEDER,
    TIM4_ENCOEDER,
    TIM5_ENCOEDER,
    TIM8_ENCOEDER = 7,
}encoder_index_enum;

int16   encoder_get_count       (encoder_index_enum encoder_n);
void    encoder_clear_count     (encoder_index_enum encoder_n);

void    encoder_quad_init       (encoder_index_enum encoder_n, encoder_channel1_enum ch1_pin, encoder_channel2_enum ch2_pin);
void    encoder_dir_init        (encoder_index_enum encoder_n, encoder_channel1_enum ch1_pin, encoder_channel2_enum ch2_pin);

#endif
