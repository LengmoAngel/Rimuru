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

#include "hal_device_registers.h"
#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_driver_gpio.h"

#include "zf_driver_timer.h"

static timer_function_enum timer_function_state[8] = 
{
    TIMER_FUNCTION_INIT, TIMER_FUNCTION_INIT,
    TIMER_FUNCTION_INIT, TIMER_FUNCTION_INIT,
    TIMER_FUNCTION_INIT, TIMER_FUNCTION_INIT,
    TIMER_FUNCTION_INIT, TIMER_FUNCTION_INIT
};

static timer_mode_enum timer_mode_state[8] = 
{
    TIMER_SYSTEM_CLOCK, TIMER_SYSTEM_CLOCK,
    TIMER_SYSTEM_CLOCK, TIMER_SYSTEM_CLOCK,
    TIMER_SYSTEM_CLOCK, TIMER_SYSTEM_CLOCK,
    TIMER_SYSTEM_CLOCK, TIMER_SYSTEM_CLOCK
};

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     TIMER 外设确认功能状态 库内部调用
// 参数说明     index           TIMER 外设模块号
// 参数说明     mode            需要确的功能模块
// 返回参数     uint8           1-可以使用 0-不可以使用
// 使用示例     zf_assert(timer_funciton_check(TIM_1, TIMER_FUNCTION_PWM);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint8 timer_funciton_check (timer_index_enum index,timer_function_enum mode)
{
    uint8 return_state = 1;
    if(TIMER_FUNCTION_INIT == timer_function_state[index])
    {
        timer_function_state[index] = mode;
    }
    else if(timer_function_state[index] == mode)
    {
        return_state = 1;
    }
    else
    {
        return_state = 0;
    }
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     TIMER 时钟使能 库内部调用
// 参数说明     index           TIMER 外设模块号
// 返回参数     void
// 使用示例     timer_clock_enable(TIM_1);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void timer_clock_enable (timer_index_enum index)
{
    switch(index)
    {
        case TIM_1:
            RCC->APB2ENR |= 0x00000001;                                         // 使能时钟
            break;
        case TIM_2:
            RCC->APB1ENR |= 0x00000001;                                         // 使能时钟
            break;
        case TIM_3:
            RCC->APB1ENR |= 0x00000001 << 1;                                    // 使能时钟
            break;
        case TIM_4:
            RCC->APB1ENR |= 0x00000001 << 2;                                    // 使能时钟
            break;
        case TIM_5:
            RCC->APB1ENR |= 0x00000001 << 3;                                    // 使能时钟
            break;
        case TIM_6:
            RCC->APB1ENR |= 0x00000001 << 4;                                    // 使能时钟
            break;
        case TIM_7:
            RCC->APB1ENR |= 0x00000001 << 5;                                    // 使能时钟
            break;
        case TIM_8:
            RCC->APB2ENR |= 0x00000001 << 1;                                    // 使能时钟
            break;
        default:
            break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     TIMER 开始计时
// 参数说明     index           TIMER 外设模块号
// 返回参数     void
// 使用示例     timer_start(TIM_1);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void timer_start (timer_index_enum index)
{
    TIM1_Type *tim_index;
    switch(index)
    {
        case TIM_1: tim_index = ((TIM1_Type *)TIM1_BASE);   break;
        case TIM_2: tim_index = ((TIM1_Type *)TIM2_BASE);   break;
        case TIM_3: tim_index = ((TIM1_Type *)TIM3_BASE);   break;
        case TIM_4: tim_index = ((TIM1_Type *)TIM4_BASE);   break;
        case TIM_5: tim_index = ((TIM1_Type *)TIM5_BASE);   break;
        case TIM_6: tim_index = ((TIM1_Type *)TIM6_BASE);   break;
        case TIM_7: tim_index = ((TIM1_Type *)TIM7_BASE);   break;
        case TIM_8: tim_index = ((TIM1_Type *)TIM8_BASE);   break;
    }
    tim_index->CR1 |= (0x00000001);                                             // 使能定时器
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     TIMER 停止计时
// 参数说明     index           TIMER 外设模块号
// 返回参数     void
// 使用示例     timer_stop(TIM_1);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void timer_stop (timer_index_enum index)
{
    TIM1_Type *tim_index;
    switch(index)
    {
        case TIM_1: tim_index = ((TIM1_Type *)TIM1_BASE);   break;
        case TIM_2: tim_index = ((TIM1_Type *)TIM2_BASE);   break;
        case TIM_3: tim_index = ((TIM1_Type *)TIM3_BASE);   break;
        case TIM_4: tim_index = ((TIM1_Type *)TIM4_BASE);   break;
        case TIM_5: tim_index = ((TIM1_Type *)TIM5_BASE);   break;
        case TIM_6: tim_index = ((TIM1_Type *)TIM6_BASE);   break;
        case TIM_7: tim_index = ((TIM1_Type *)TIM7_BASE);   break;
        case TIM_8: tim_index = ((TIM1_Type *)TIM8_BASE);   break;
    }
    tim_index->CR1 &= (0xFFFFFFFE);                                             // 停止定时器
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     TIMER 获取计时器计数
// 参数说明     index           TIMER 外设模块号
// 返回参数     uint16          计数值
// 使用示例     timer_get(TIM_1);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint16 timer_get (timer_index_enum index)
{
    TIM1_Type *tim_index;
    uint16 return_value = 0;
    switch(index)
    {
        case TIM_1: tim_index = ((TIM1_Type *)TIM1_BASE);   break;
        case TIM_2: tim_index = ((TIM1_Type *)TIM2_BASE);   break;
        case TIM_3: tim_index = ((TIM1_Type *)TIM3_BASE);   break;
        case TIM_4: tim_index = ((TIM1_Type *)TIM4_BASE);   break;
        case TIM_5: tim_index = ((TIM1_Type *)TIM5_BASE);   break;
        case TIM_6: tim_index = ((TIM1_Type *)TIM6_BASE);   break;
        case TIM_7: tim_index = ((TIM1_Type *)TIM7_BASE);   break;
        case TIM_8: tim_index = ((TIM1_Type *)TIM8_BASE);   break;
    }
    if(TIMER_MS == timer_mode_state[index])
    {
        return_value = (uint16)tim_index->CNT / 2;
    }
    else
    {
        return_value = (uint16)tim_index->CNT;
    }
    return return_value;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     TIMER 清除计时器计数
// 参数说明     index           TIMER 外设模块号
// 返回参数     void
// 使用示例     timer_clear(TIM_1);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void timer_clear (timer_index_enum index)
{
    switch(index)
    {
        case TIM_1: TIM1->EGR |= 0x01;  break;
        case TIM_2: TIM2->EGR |= 0x01;  break;
        case TIM_3: TIM3->EGR |= 0x01;  break;
        case TIM_4: TIM4->EGR |= 0x01;  break;
        case TIM_5: TIM5->EGR |= 0x01;  break;
        case TIM_6: TIM6->EGR |= 0x01;  break;
        case TIM_7: TIM7->EGR |= 0x01;  break;
        case TIM_8: TIM8->EGR |= 0x01;  break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     TIMER 计时器初始化
// 参数说明     index           TIMER 外设模块号
// 参数说明     mode            计时方式
// 返回参数     void
// 使用示例     timer_init(TIM_1, TIMER_US);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void timer_init (timer_index_enum index, timer_mode_enum mode)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 就去查看你在什么地方调用这个函数 检查你的传入参数
    // 这里是检查是否有重复使用定时器
    // 比如初始化了 TIM1_PWM 然后又初始化成 TIM_1 这种用法是不允许的
    zf_assert(timer_funciton_check(index, TIMER_FUNCTION_TIMER));
    timer_function_state[index] = TIMER_FUNCTION_TIMER;

    timer_clock_enable(index);                                                  // 使能时钟
    TIM1_Type *tim_index;
    switch(index)
    {
        case TIM_1: tim_index = ((TIM1_Type *)TIM1_BASE);   break;
        case TIM_2: tim_index = ((TIM1_Type *)TIM2_BASE);   break;
        case TIM_3: tim_index = ((TIM1_Type *)TIM3_BASE);   break;
        case TIM_4: tim_index = ((TIM1_Type *)TIM4_BASE);   break;
        case TIM_5: tim_index = ((TIM1_Type *)TIM5_BASE);   break;
        case TIM_6: tim_index = ((TIM1_Type *)TIM6_BASE);   break;
        case TIM_7: tim_index = ((TIM1_Type *)TIM7_BASE);   break;
        case TIM_8: tim_index = ((TIM1_Type *)TIM8_BASE);   break;
        default: return;
    }

    timer_mode_state[index] = mode;
    switch(mode)
    {
        case TIMER_US:
            tim_index->ARR |= 0x0000FFFF;                                       // 装载自动重装载值
            if(SYSTEM_CLOCK_120M < system_clock)
            {
                tim_index->PSC = system_clock / 2/ 1000000 - 1;                 // 装载预分频
            }
            else
            {
                tim_index->PSC = system_clock / 1000000 - 1;                    // 装载预分频
            }
            break;
        case TIMER_MS:
            tim_index->ARR |= 0x0000FFFF;                                       // 装载自动重装载值
            if(SYSTEM_CLOCK_120M < system_clock)
            {
                tim_index->PSC = (system_clock / 2 / 1000) / 2 - 1;             // 装载预分频
            }
            else
            {
                tim_index->PSC = (system_clock / 1000) / 2 - 1;                 // 装载预分频
            }
            break;
        default:
            tim_index->ARR |= 0x0000FFFF;                                       // 装载自动重装载值
            tim_index->PSC = 0;                                                 // 装载预分频
            break;
    }

    tim_index->EGR |= 0x01;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     TIMER ETR 外部时钟输入功能初始化 32类单片机用于驱动摄像头 库内部调用
// 参数说明     pin             ETR 引脚
// 参数说明     sign            信号类型 上升沿或者下降沿
// 返回参数     void
// 使用示例     timer_etr_init(OV7725_PCLK_PIN, TIM_ETR_FALLING);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void timer_etr_init (timer_etr_pin_emun pin, timer_etr_mode_emun sign)
{
    timer_index_enum index = (timer_index_enum)((pin & 0xF000) >> 12);

    zf_assert(timer_funciton_check(index, TIMER_FUNCTION_CAMERA));
    timer_clock_enable(index);

    TIM1_Type *tim_index;
    switch(index)
    {
        case TIM_1: tim_index = ((TIM1_Type *)TIM1_BASE);   break;
        case TIM_2: tim_index = ((TIM1_Type *)TIM2_BASE);   break;
        case TIM_3: tim_index = ((TIM1_Type *)TIM3_BASE);   break;
        case TIM_4: tim_index = ((TIM1_Type *)TIM4_BASE);   break;
        case TIM_5: tim_index = ((TIM1_Type *)TIM5_BASE);   break;
        case TIM_6: tim_index = ((TIM1_Type *)TIM6_BASE);   break;
        case TIM_7: tim_index = ((TIM1_Type *)TIM7_BASE);   break;
        case TIM_8: tim_index = ((TIM1_Type *)TIM8_BASE);   break;
    }

    afio_init((gpio_pin_enum)(pin & 0x00FF), GPI, (gpio_af_enum)((pin & 0x0F00) >> 8), GPI_FLOATING_IN);    // 提取对应IO索引 AF功能编码

    tim_index->ARR |= 0x0000FFFF;                                               // 装载自动重装载值
    tim_index->PSC = 0;                                                         // 装载预分频
    tim_index->EGR |= 0x01;

    uint32 temp = tim_index->SMCR;
    temp &= 0xFFFF0088;
    temp |= 0x00000074;
    tim_index->SMCR = temp;
    if(TIM_ETR_FALLING == sign)
    {
        tim_index->SMCR |= 0x00008000;
    }
    tim_index->DIER |= 0x00004000;
    tim_index->CR1 |= (0x00000001);                                             // 使能定时器
}

