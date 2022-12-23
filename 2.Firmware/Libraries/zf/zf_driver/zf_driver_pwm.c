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
* 文件名称          zf_driver_pwm
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
#include "zf_driver_gpio.h"
#include "zf_driver_timer.h"

#include "zf_driver_pwm.h"

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     PWM 更新占空比
// 参数说明     pin             选择 PWM 引脚
// 参数说明     duty            设置占空比
// 返回参数     void
// 使用示例     pwm_set_duty(TIM5_PWMCH1_A0, PWM_DUTY_MAX / 4);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void pwm_set_duty (pwm_channel_enum pin, const uint32 duty)
{
    // 如果是这一行报错 那你得去看看最大占空比是限定的多少 占空比写入错误
    zf_assert(PWM_DUTY_MAX >= duty);                                            // 占空比写入错误

    TIM1_Type *tim_index;
    switch((pin & 0xF0000) >> 16)
    {
        case 0: tim_index = ((TIM1_Type *)TIM1_BASE);   break;
        case 1: tim_index = ((TIM1_Type *)TIM2_BASE);   break;
        case 2: tim_index = ((TIM1_Type *)TIM3_BASE);   break;
        case 3: tim_index = ((TIM1_Type *)TIM4_BASE);   break;
        case 4: tim_index = ((TIM1_Type *)TIM5_BASE);   break;
        case 7: tim_index = ((TIM1_Type *)TIM8_BASE);   break;
    }
    uint16 period_temp = tim_index->ARR;                                        // 获取自动重装载值
    uint16 match_temp = (uint16)(period_temp * ((float)duty / PWM_DUTY_MAX));   // 计算占空比
    if(match_temp == period_temp)   match_temp +=1;

    switch(pin&0x0F000)                                                         // 提取通道值
    {
        case 0x01000:
            tim_index->CCR[0] = match_temp;                                     // 装载比较值
            break;
        case 0x02000:
            tim_index->CCR[1] = match_temp;                                     // 装载比较值
            break;
        case 0x03000:
            tim_index->CCR[2] = match_temp;                                     // 装载比较值
            break;
        case 0x04000:
            tim_index->CCR[3] = match_temp;                                     // 装载比较值
            break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     PWM 初始化
// 参数说明     pin             选择 PWM 引脚
// 参数说明     freq            设置频率 同个模块只有最后一次设置生效
// 参数说明     duty            设置占空比
// 返回参数     void
// 使用示例     pwm_init(TIM5_PWMCH1_A0, 17000, PWM_DUTY_MAX / 2);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void pwm_init (pwm_channel_enum pin, const uint32 freq, const uint32 duty)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 就去查看你在什么地方调用这个函数 检查你的传入参数
    // 这里是检查是否有重复使用定时器
    // 比如初始化了 TIM1_PIT 然后又初始化成 TIM1_PWM 这种用法是不允许的
    zf_assert(timer_funciton_check((timer_index_enum)((pin & 0xF0000) >> 16), TIMER_FUNCTION_PWM));
    // 如果是这一行报错 那你得去看看最大占空比是限定的多少 占空比写入错误
    zf_assert(PWM_DUTY_MAX >= duty);

    TIM1_Type *tim_index;
    uint16 freq_div;                                                            // 计算预分频
    uint16 period_temp;                                                         // 计算自动重装载值
    if(SYSTEM_CLOCK_120M < system_clock)
    {
        freq_div = ((system_clock / 2 / freq) >> 15);                           // 计算预分频
        period_temp = (system_clock / 2 / freq / (freq_div + 1));               // 计算自动重装载值
    }
    else
    {
        freq_div = ((system_clock / freq) >> 15);                               // 计算预分频
        period_temp = (system_clock / freq / (freq_div + 1));                   // 计算自动重装载值
    }
    uint16 match_temp = (uint16)(period_temp *((float)duty / PWM_DUTY_MAX));    // 计算占空比

    timer_clock_enable((timer_index_enum)((pin & 0xF0000) >> 16));
    afio_init((gpio_pin_enum)(pin & 0x000FF), GPO, (gpio_af_enum)((pin & 0x00F00) >> 8), GPO_AF_PUSH_PULL); // 初始化引脚

    switch((pin & 0xF0000) >> 16)
    {
        case 0: tim_index = ((TIM1_Type *)TIM1_BASE);   break;
        case 1: tim_index = ((TIM1_Type *)TIM2_BASE);   break;
        case 2: tim_index = ((TIM1_Type *)TIM3_BASE);   break;
        case 3: tim_index = ((TIM1_Type *)TIM4_BASE);   break;
        case 4: tim_index = ((TIM1_Type *)TIM5_BASE);   break;
        case 7: tim_index = ((TIM1_Type *)TIM8_BASE);   break;
    }

    tim_index->ARR = period_temp;                                               // 装载自动重装载值
    tim_index->PSC = freq_div;                                                  // 装载预分频
    tim_index->CR1 = (0x00000001 << 7);                                         // 允许自动重装载值的预装载
    tim_index->BDTR = (0x00000001 << 15);                                       // PWM 输出使能

    switch(pin & 0x0F000)
    {
        case 0x01000:
            tim_index->CCMR1 |= (0x00000006 << 4);                              // OC1M [6:4] 110 PWM 模式 1
            tim_index->CCMR1 |= (0x00000001 << 3);                              // 允许输出比较值的预装载
            tim_index->CCER |= (0x000000001);                                   // 使能通道 1
            tim_index->CCR[0] = match_temp;                                     // 装载比较值
            break;
        case 0x02000:
            tim_index->CCMR1 |= (0x00000006 << 12);                             // OC2M [14:12] 110 PWM 模式 1
            tim_index->CCMR1 |= (0x00000001 << 11);                             // 允许输出比较值的预装载
            tim_index->CCER |= (0x000000001 << 4);                              // 使能通道 2
            tim_index->CCR[1] = match_temp;                                     // 装载比较值
            break;
        case 0x03000:
            tim_index->CCMR2 |= (0x00000006 << 4);                              // OC1M [6:4] 110 PWM 模式 1
            tim_index->CCMR2 |= (0x00000001 << 3);                              // 允许输出比较值的预装载
            tim_index->CCER |= (0x000000001 << 8);                              // 使能通道 2
            tim_index->CCR[2] = match_temp;                                     // 装载比较值
            break;
        case 0x04000:
            tim_index->CCMR2 |= (0x00000006 << 12);                             // OC1M [6:4] 110 PWM 模式 1
            tim_index->CCMR2 |= (0x00000001 << 11);                             // 允许输出比较值的预装载
            tim_index->CCER |= (0x000000001 << 12);                             // 使能通道 2
            tim_index->CCR[3] = match_temp;                                     // 装载比较值
            break;
    }

    tim_index->CR1 |= (0x000000001);                                            // 使能定时器
}
