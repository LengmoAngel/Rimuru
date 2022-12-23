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
* 文件名称          zf_driver_exti
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

#include "zf_driver_exti.h"

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     EXTI 中断使能
// 参数说明     pin             选择 EXTI 引脚 (可选择范围由 zf_driver_gpio.h 内 gpio_pin_enum 枚举值确定)
// 返回参数     void
// 使用示例     exti_enable(A0);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void exti_enable (gpio_pin_enum pin)
{
    EXTI->IMR |= (0x00000001 << (pin & 0x1F));
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     EXTI 中断失能
// 参数说明     pin             选择 EXTI 引脚 (可选择范围由 zf_driver_gpio.h 内 gpio_pin_enum 枚举值确定)
// 返回参数     void
// 使用示例     exti_disable(A0);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void exti_disable (gpio_pin_enum pin)
{
    EXTI->IMR &= ~(0x00000001 << (pin & 0x1F));
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     EXTI 中断初始化
// 参数说明     pin             选择 EXTI 引脚 (可选择范围由 zf_driver_gpio.h 内 gpio_pin_enum 枚举值确定)
// 参数说明     trigger         选择触发的信号方式 [EXTI_TRIGGER_RISING/EXTI_TRIGGER_FALLING/EXTI_TRIGGER_BOTH]
// 返回参数     void
// 使用示例     exti_init(A0, EXTI_TRIGGER_RISING);
// 备注信息     同一下标的引脚不能同时初始化为外部中断输入 例如 A0 和 B0 不能同时初始化为外部中断输入
//-------------------------------------------------------------------------------------------------------------------
void exti_init (gpio_pin_enum pin, exti_trigger_enum trigger)
{
    uint32 register_temp = 0;
    gpio_init(pin, GPI, GPIO_HIGH, GPI_PULL_UP);                                // 初始化选中的引脚

    RCC->APB2ENR |= RCC_APB2ENR_SYSCFG(1);                                      // 先使能 SYSCFG
    EXTI->IMR &= ~(0x00000001 << (pin & 0x1f));                                 // 禁止 Line 的中断

    switch((pin & 0x1F) / 0x04)                                                 // 计算对应在哪个寄存器设置
    {
        case 0: register_temp = SYSCFG->EXTICR1;    break;                      // 0-3 Line
        case 1: register_temp = SYSCFG->EXTICR2;    break;                      // 4-7 Line
        case 2: register_temp = SYSCFG->EXTICR3;    break;                      // 8-11 Line
        case 3: register_temp = SYSCFG->EXTICR4;    break;                      // 12-15 Line
    }
    switch(pin%0x04)
    {
        case 0: 
            register_temp &= 0xFFFFFFF0;                                        // 清空 Line12/8/4/0 原有设置 防止写入触发异常
            register_temp |= ((0x000000f0 & pin) >> 5);                         // Line12/8/4/0 - [ 3: 0] 写入对应引脚组别号
            break;
        case 1: 
            register_temp &= 0xFFFFFF0F;                                        // 清空 Line13/9/5/1 原有设置 防止写入触发异常
            register_temp |= ((0x000000f0 & pin) >> 5) << 4;                    // Line13/9/5/1 - [ 7: 4] 写入对应引脚组别号
            break;
        case 2: 
            register_temp &= 0xFFFFF0FF;                                        // 清空 Line14/10/6/2 原有设置 防止写入触发异常
            register_temp |= ((0x000000f0 & pin) >> 5) << 8;                    // Line14/10/6/2 - [11: 8] 写入对应引脚组别号
            break;
        case 3: 
            register_temp &= 0xFFFF0FFF;                                        // 清空 Line15/11/7/3 原有设置 防止写入触发异常
            register_temp |= ((0x000000f0 & pin) >> 5) << 12;                   // Line15/11/7/3 - [15:12] 写入对应引脚组别号
            break;
    }
    switch((pin & 0x1F) / 0x04)                                                 // 计算对应在哪个寄存器设置
    {
        case 0: SYSCFG->EXTICR1 = register_temp;    break;                      // 0-3 Line
        case 1: SYSCFG->EXTICR2 = register_temp;    break;                      // 4-7 Line
        case 2: SYSCFG->EXTICR3 = register_temp;    break;                      // 8-11 Line
        case 3: SYSCFG->EXTICR4 = register_temp;    break;                      // 12-15 Line
    }

    switch(trigger)
    {
        case EXTI_TRIGGER_RISING:                                               // 上升沿触发模式
            EXTI->RTSR |= (0x00000001 << (pin & 0x1f));                         // 上升沿触发使能
            EXTI->FTSR &= ~(0x00000001 << (pin & 0x1f));                        // 下降沿触发禁止
            break;
        case EXTI_TRIGGER_FALLING:                                              // 下降沿触发模式
            EXTI->RTSR &= ~(0x00000001 << (pin & 0x1f));                        // 上升沿触发禁止
            EXTI->FTSR |= (0x00000001 << (pin & 0x1f));                         // 下降沿触发使能
            break;
        case EXTI_TRIGGER_BOTH:                                                 // 双边沿触发模式
            EXTI->RTSR |= (0x00000001 << (pin & 0x1f));                         // 上升沿触发使能
            EXTI->FTSR |= (0x00000001 << (pin & 0x1f));                         // 下降沿触发使能
            break;
    }
    EXTI->IMR |= (0x00000001 << (pin & 0x1f));                                  // 使能 Line 的中断

    switch((pin & 0x1F))                                                        // 计算对应在哪个寄存器设置
    {
        case 0:
            interrupt_enable(EXTI0_IRQn);                                       // 使能 Line0 的中断响应
            break;
        case 1:
            interrupt_enable(EXTI1_IRQn);                                       // 使能 Line1 的中断响应
            break;
        case 2:
            interrupt_enable(EXTI2_IRQn);                                       // 使能 Line2 的中断响应
            break;
        case 3:
            interrupt_enable(EXTI3_IRQn);                                       // 使能 Line3 的中断响应
            break;
        case 4:
            interrupt_enable(EXTI4_IRQn);                                       // 使能 Line4 的中断响应
            break;
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            interrupt_enable(EXTI9_5_IRQn);                                     // 使能 Line5-9 的中断响应
            break;
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
            interrupt_enable(EXTI15_10_IRQn);                                   // 使能 Line10-15 的中断响应
            break;
        default:
            break;
    }
}
