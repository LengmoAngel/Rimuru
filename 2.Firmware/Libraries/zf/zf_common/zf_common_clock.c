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
* 文件名称          zf_common_clock
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

#include "zf_common_function.h"
#include "zf_common_interrupt.h"

#include "zf_common_clock.h"

uint32 system_clock = SYSTEM_CLOCK_96M;                                         // 系统时钟信息

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     核心时钟恢复初始设置
// 参数说明     void
// 返回参数     void
// 使用示例     clock_reset();
// 备注信息     本函数在文件内部调用 用户不用关注 也不可修改
//-------------------------------------------------------------------------------------------------------------------
static void clock_reset (void)
{
    RCC->CR |= 0x00000001;                                                      // 使能内部高速时钟

    RCC->CFGR &= 0xF8FFC00C;                                                    // 清空 SW[1:0]       = 00    选择 HSI 用作系统时钟
                                                                                // 清空 HPRE[7:4]     = 0xxx  HCLK = SYSCLK 不分频
                                                                                // 清空 PPRE1[10:8]   = 0xx   APB1 = HCLK 不分频
                                                                                // 清空 PPRE2[13:11]  = 0xx   APB2 = HCLK 不分频
                                                                                // 清空 MCO[26:24]    = 00x   没有时钟输出

    RCC->CR &= 0xFEF6FFFF;                                                      // 清空 HSEON[16]     = 0     禁用高速外部晶体振荡器
                                                                                // 清空 CSSON[19]     = 0     禁用时钟探测器
                                                                                // 清空 PLLON[24]     = 0     禁用 PLL

    RCC->CR &= 0xFFFBFFFF;                                                      // 清空 HSEBYP[18]    = 0     禁用高速外部晶体振荡器旁路模式

    RCC->CFGR &= 0xFF3CFFFF;                                                    // 清空 Res[16:17]    = 00
                                                                                // 清空 USBPRE[23:22] = 00    PLL 时钟直接作为 USB 时钟

    RCC->CR &= 0x008FFFFF;                                                      // 清空 Res[22:20]    = 000
                                                                                // 清空 PLLON[24]     = 0     禁用 PLL
                                                                                // 清空 PLLRDY[25]    = 0     PLL 未稳定
                                                                                // 清空 Res[26:31]    = 00000

    RCC->CIR = 0x009F0000;                                                      // 禁用所有中断并清除挂起位

    CACHE->CCR &= ~(0x3 << 3);                                                  // 设置 <自动 SRAM 电源请求> 并 <当 cache 使能后自动 cache 失效模式>
    CACHE->CCR |= 1;                                                            // 使能 cache
    while(2 != (CACHE->SR & 0x3));                                              // 确认 Cache 已使能
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     核心时钟设置
// 参数说明     clock       时钟频率 推荐使用 zf_common_clock.h 中 system_clock_enum 定义的选项
// 返回参数     void
// 使用示例     clock_set_freq(clock);
// 备注信息     本函数在文件内部调用 用户不用关注 也不可修改
//-------------------------------------------------------------------------------------------------------------------
static void clock_set_freq (uint32 clock)
{
    volatile uint32 hse_status = 0;
    volatile uint32 temp_value = 0;

    RCC->CR |= 0x00010000;                                                      // 设置 HSEON[16]     = 1     使能高速外部晶体振荡器

    if(clock > 96000000)
    {
        temp_value = RCC->APB1ENR;
        temp_value |= 0x10000000;
        RCC->APB1ENR = temp_value;
        temp_value = PWR->CR1;
        temp_value &= 0xFFFF3FFF;
        temp_value |= 0x0000C000;
        PWR->CR1 = temp_value;
    }

    temp_value = 0;
    do
    {
        hse_status = RCC->CR & 0x00020000;                                      // 获取高速外部晶体振荡器状态
        temp_value ++;                                                          // 超时计数
    }while((0x00000000 == hse_status) && (XTAL_STARTUP_TIMEOUT != temp_value)); // 高速外部晶体振荡器已稳定或者超时退出

    if(0x00000000 != (RCC->CR & 0x00020000))                                    // 高速外部晶体振荡器已稳定
    {
        hse_status = 0x00000001;                                                // 标志进入下一个时钟配置状态
        temp_value = 2000;                                                      // 设置延时
        while(temp_value --);                                                   // 延时稳定时钟
    }
    else
    {
        hse_status = 0x00000000;                                                // 高速外部晶体振荡器未稳定 进入错误状态
    }

    if(0x00000001 == hse_status)
    {
        FLASH->ACR |= 0x00000010;                                               // 启用预取缓冲区
        FLASH->ACR &= ~0x00000007;                                              // 清空 Flash 时延
        FLASH->ACR |= (((clock - 1) / 24000000) & 0x00000007);                  // 计算并设置 Latency 时延

        RCC->CFGR |= (((clock - 1) / 120000000) ? 0x00000080 : 0);              // 如果时钟频率超过 120Mhz 就需要分频

        if(SYSTEM_CLOCK_XTAL == clock)
        {
            RCC->CFGR &= 0xFFFFFFFC;                                            // 清空 SW[1:0]       = 00    选择 HSI 用作系统时钟
            RCC->CFGR |= 0x00000001;                                            // 设置 SW[1:0]       = 01    选择 HSE 用作系统时钟

            while(0x00000004 != (RCC->CFGR & 0x0000000C));                      // 等待切换到 HSE 时钟
        }
        else
        {
            RCC->PLLCFGR &= 0xFFFFFFFC;                                         // 清空 [1:0]         = 00    HSI 时钟用作 PLL 输入时钟 HSE 不分频
            RCC->PLLCFGR |= 0x00000001;                                         // 设置 [1:0]         = 01    HSE 时钟用作 PLL 输入时钟 HSE 不分频

            RCC->APB1ENR |= 0x10000000;                                         // 设置 PWR[28]       = 1     电源接口/DBG 时钟开启
            temp_value = func_get_greatest_common_divisor(clock, SYSTEM_CLOCK_XTAL);    // 获取目标时钟与晶振频率的最大公约数
            RCC->PLLCFGR &= 0xFF80F8FF;                                         // 清空 PLLDIV[10:8] PLL 分频系数 PLLMUL[22:16] PLL 倍频系数
            RCC->PLLCFGR |= ((uint32)(SYSTEM_CLOCK_XTAL / temp_value - 1) << 8);// 计算并写入 PLL 分频系数
            RCC->PLLCFGR |= ((uint32)(clock / temp_value - 1) << 16);           // 计算并写入 PLL 倍频系数

            RCC->CR |= 0x01000000;                                              // 设置 PLLON[24]     = 1     使能 PLL

            while(0 == (RCC->CR & 0x02000000));                                 // 等待 PLL 未稳定

            RCC->CFGR &= 0xFFFFFFFC;                                            // 清空 SW[1:0]       = 00    选择 HSI 用作系统时钟
            RCC->CFGR |= 0x00000002;                                            // 设置 SW[1:0]       = 01    选择 PLL 输出用作系统时钟

            while(0x00000008 != (RCC->CFGR & 0x0000000C));                      // 等待切换到 PLL 时钟
        }
    }
    else
    {
        while(1);                                                               // 外部晶振不稳定或缺失 时钟设置失败
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     核心时钟初始化
// 参数说明     clock       时钟频率 推荐使用 zf_common_clock.h 中 system_clock_enum 定义的选项
// 返回参数     void
// 使用示例     clock_init(SYSTEM_CLOCK_120M);                  // 初始化核心时钟为 120MHz
// 备注信息     本函数用于将核心时钟设置到指定频率
//-------------------------------------------------------------------------------------------------------------------
void clock_init (uint32 clock)
{
    system_clock = clock;                                                       // 记录核心时钟频率
    clock_reset();
    clock_set_freq(clock);
    interrupt_init();
}
