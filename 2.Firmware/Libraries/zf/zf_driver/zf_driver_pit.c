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
* 文件名称          zf_driver_pit
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
#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_common_interrupt.h"
#include "zf_driver_timer.h"

#include "zf_driver_pit.h"

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     PIT 中断使能
// 参数说明     pit_n           PIT 外设模块号
// 返回参数     void
// 使用示例     pit_enable(TIM1_PIT);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void pit_enable (pit_index_enum pit_n)
{
    switch(pit_n)
    {
        case TIM1_PIT: TIM1->CR1 |= (0x00000001);  break;
        case TIM2_PIT: TIM2->CR1 |= (0x00000001);  break;
        case TIM3_PIT: TIM3->CR1 |= (0x00000001);  break;
        case TIM4_PIT: TIM4->CR1 |= (0x00000001);  break;
        case TIM5_PIT: TIM5->CR1 |= (0x00000001);  break;
        case TIM6_PIT: TIM6->CR1 |= (0x00000001);  break;
        case TIM7_PIT: TIM7->CR1 |= (0x00000001);  break;
        case TIM8_PIT: TIM8->CR1 |= (0x00000001);  break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     PIT 中断禁止
// 参数说明     pit_n           PIT 外设模块号
// 返回参数     void
// 使用示例     pit_disable(TIM1_PIT);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void pit_disable (pit_index_enum pit_n)
{
    switch(pit_n)
    {
        case TIM1_PIT: TIM1->CR1 &= ~(0x00000001); break;
        case TIM2_PIT: TIM2->CR1 &= ~(0x00000001); break;
        case TIM3_PIT: TIM3->CR1 &= ~(0x00000001); break;
        case TIM4_PIT: TIM4->CR1 &= ~(0x00000001); break;
        case TIM5_PIT: TIM5->CR1 &= ~(0x00000001); break;
        case TIM6_PIT: TIM6->CR1 &= ~(0x00000001); break;
        case TIM7_PIT: TIM7->CR1 &= ~(0x00000001); break;
        case TIM8_PIT: TIM8->CR1 &= ~(0x00000001); break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     PIT 初始化 一般调用 pit_ms_init 或 pit_us_init
// 参数说明     pit_n           PIT 外设模块号
// 参数说明     period          PIT 周期 一般是芯片或者模块时钟频率计算
// 返回参数     void
// 使用示例     pit_init(TIM1_PIT, 120);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void pit_init (pit_index_enum pit_n, uint32 period)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 就去查看你在什么地方调用这个函数 检查你的传入参数
    // 这里是检查是否有重复使用定时器
    // 比如初始化了 TIM1_PWM 然后又初始化成 TIM1_PIT 这种用法是不允许的
    zf_assert(timer_funciton_check((timer_index_enum)pit_n, TIMER_FUNCTION_TIMER));
    // 如果是这一行报错 那我就得问问你为什么周期写的是 0
    zf_assert(period != 0);

    if(SYSTEM_CLOCK_120M < system_clock)
    {
        period /= 2;
    }
    uint16 freq_div = (period >> 15);                                           // 计算预分频
    uint16 period_temp = (period / (freq_div + 1));                             // 计算自动重装载值

    timer_clock_enable((timer_index_enum)pit_n);                                // 使能时钟
    TIM1_Type *tim_index;
    switch(pit_n)
    {
        case TIM1_PIT: tim_index = ((TIM1_Type *)TIM1_BASE);   break;
        case TIM2_PIT: tim_index = ((TIM1_Type *)TIM2_BASE);   break;
        case TIM3_PIT: tim_index = ((TIM1_Type *)TIM3_BASE);   break;
        case TIM4_PIT: tim_index = ((TIM1_Type *)TIM4_BASE);   break;
        case TIM5_PIT: tim_index = ((TIM1_Type *)TIM5_BASE);   break;
        case TIM6_PIT: tim_index = ((TIM1_Type *)TIM6_BASE);   break;
        case TIM7_PIT: tim_index = ((TIM1_Type *)TIM7_BASE);   break;
        case TIM8_PIT: tim_index = ((TIM1_Type *)TIM8_BASE);   break;
    }

    tim_index->ARR = period_temp;                                               // 装载自动重装载值
    tim_index->PSC = freq_div;                                                  // 装载预分频
    tim_index->DIER |= (0x00000001);                                            // 使能中断更新

    IRQn_Type irq_index[8] = {
        TIM1_UP_IRQn,   TIM2_IRQn,  TIM3_IRQn,  TIM4_IRQn,
        TIM5_IRQn,      TIM6_IRQn,  TIM7_IRQn,  TIM8_UP_IRQn };

    interrupt_enable(irq_index[(pit_n)]);

//    tim_index->EGR |= 0x01;
    tim_index->CR1 |= (0x00000001);                                             // 使能定时器
}
