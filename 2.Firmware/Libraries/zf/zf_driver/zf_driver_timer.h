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
* 文件名称          zf_driver_timer
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

#ifndef _zf_driver_timer_h_
#define _zf_driver_timer_h_

#include "zf_common_typedef.h"

typedef enum
{
    TIM_1,
    TIM_2,
    TIM_3,
    TIM_4,
    TIM_5,
    TIM_6,
    TIM_7,
    TIM_8,
}timer_index_enum;

typedef enum
{
    TIMER_SYSTEM_CLOCK,                                                         // 系统频率计时 最大 0xFFFF
    TIMER_US,                                                                   // 微秒计时 最大 0xFFFF
    TIMER_MS,                                                                   // 毫秒计时 最大 0xFFFF/2
}timer_mode_enum;

typedef enum
{
    TIMER_FUNCTION_INIT = 0,                                                    // 功能未初始化
    TIMER_FUNCTION_TIMER,                                                       // 用作 TIMER 计时
    TIMER_FUNCTION_PIT,                                                         // 用作 PIT
    TIMER_FUNCTION_PWM,                                                         // 用作 PWM
    TIMER_FUNCTION_ENCODER,                                                     // 用作 ENCODER
    TIMER_FUNCTION_CAMERA,                                                      // 用作 CAMERA
}timer_function_enum;

// 枚举 TIM_ETR 输入引脚  此枚举定义不允许用户修改
typedef enum                                                                    // 枚举 TIM_ETR 通道
{
    TIM1_ETR_A12            = 0x010C,                                           // 0x 0[TIM1] 1[AF1] 0C[A12]
    TIM1_ETR_E7             = 0x0187,                                           // 0x 0[TIM1] 1[AF1] 87[E7]

    TIM2_ETR_A0             = 0x1100,                                           // 0x 1[TIM2] 1[AF1] 00[A0]
    TIM2_ETR_A5             = 0x1105,                                           // 0x 1[TIM2] 1[AF1] 05[A5]
    TIM2_ETR_A15            = 0x110F,                                           // 0x 1[TIM2] 1[AF1] 0F[A15]

    TIM3_ETR_D2             = 0x2262,                                           // 0x 2[TIM3] 2[AF2] 62[D2]

    TIM4_ETR_E0             = 0x3280,                                           // 0x 3[TIM4] 2[AF2] 80[E0]

    TIM8_ETR_A0             = 0x7300,                                           // 0x 7[TIM8] 3[AF3] 00[A0]
}timer_etr_pin_emun;

typedef enum
{
    TIM_ETR_RISING,
    TIM_ETR_FALLING,
}timer_etr_mode_emun;

uint8       timer_funciton_check        (timer_index_enum index, timer_function_enum mode);
void        timer_clock_enable          (timer_index_enum index);

void        timer_start                 (timer_index_enum index);
void        timer_stop                  (timer_index_enum index);
uint16      timer_get                   (timer_index_enum index);
void        timer_clear                 (timer_index_enum index);

void        timer_init                  (timer_index_enum index, timer_mode_enum mode);
void        timer_etr_init              (timer_etr_pin_emun pin, timer_etr_mode_emun sign);

#endif
