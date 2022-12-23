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
* 文件名称          zf_driver_gpio
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

#include "zf_driver_gpio.h"

GPIO_Type *gpio_group[8] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH};

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     gpio 输出设置
// 参数说明     pin         选择的引脚 (可选择范围由 zf_driver_gpio.h 内 gpio_pin_enum 枚举值确定)
// 参数说明     dat         0：低电平 1：高电平
// 返回参数     void
// 使用示例     gpio_set_level(D5, 1);                                          // D5 输出高电平
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void gpio_set_level (gpio_pin_enum pin, const uint8 dat)
{
    if(dat)
    {
        gpio_high(pin);                                                         // 输出高电平
    }
    else
    {
        gpio_low(pin);                                                          // 输出低电平
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     gpio 电平获取
// 参数说明     pin         选择的引脚 (可选择范围由 zf_driver_gpio.h 内 gpio_pin_enum 枚举值确定)
// 返回参数     uint8       引脚当前电平
// 使用示例     uint8 status = gpio_get_level(D5);                              // 获取 D5 引脚电平
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint8 gpio_get_level (gpio_pin_enum pin)
{
    return ((gpio_group[(pin & 0xE0) >> 5]->IDR & (((uint16)0x0001) << (pin & 0x1F))) ? 1 : 0);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     gpio 翻转电平
// 参数说明     pin         选择的引脚 (可选择范围由 zf_driver_gpio.h 内 gpio_pin_enum 枚举值确定)
// 返回参数     void
// 使用示例     gpio_toggle_level(D5);                                          // 翻转 D5 电平
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void gpio_toggle_level (gpio_pin_enum pin)
{
    if(gpio_group[(pin & 0xE0) >> 5]->IDR & (((uint16)0x0001) << (pin & 0x1F)))
    {
        gpio_group[(pin & 0xE0) >> 5]->BRR |= (((uint16)0x0001) << (pin & 0x1F));   // 输出低电平
    }
    else
    {
        gpio_group[(pin & 0xE0) >> 5]->BSRR |= (((uint16)0x0001) << (pin & 0x1F));  // 输出高电平
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     gpio 方向设置
// 参数说明     pin         选择的引脚 (可选择范围由 zf_driver_gpio.h 内 gpio_pin_enum 枚举值确定)
// 参数说明     dir         引脚的方向   输出：GPO   输入：GPI
// 参数说明     mode        引脚的模式 (可选择范围由 zf_driver_gpio.h 内 gpio_mode_enum 枚举值确定)
// 返回参数     void
// 使用示例     gpio_set_dir(D5, GPI, GPI_PULL_UP);                             // 设置 D5 为上拉输入
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void gpio_set_dir (gpio_pin_enum pin, gpio_dir_enum dir, gpio_mode_enum mode)
{
    uint32 temp = 0;
    uint8 io_group = ((pin & 0xE0) >> 5);                                       // 提取IO分组
    uint8 io_pin = (pin & 0x1F);                                                // 提取IO引脚下标
    if(0x08 > io_pin)                                                           // 低8位引脚
    {
        temp = gpio_group[io_group]->CRL;
        temp &= ~(0x0000000f << (io_pin * 4));                                  // 清空模式
        temp |= (((uint32)dir | (uint32)(mode & 0x0C)) << (io_pin * 4));        // 写入对应模式
        gpio_group[io_group]->CRL = temp;
    }
    else                                                                        // 高8位引脚
    {
        temp = gpio_group[io_group]->CRH;
        temp &= ~(0x0000000f << ((io_pin - 8) * 4));                            // 清空模式
        temp |= (((uint32)dir | (uint32)(mode & 0x0C)) << ((io_pin - 8) * 4));  // 写入对应模式
        gpio_group[io_group]->CRH = temp;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     gpio 初始化
// 参数说明     pin         选择的引脚 (可选择范围由 zf_driver_gpio.h 内 gpio_pin_enum 枚举值确定)
// 参数说明     mode        引脚的方向 [GPI/GPIO]
// 参数说明     dat         引脚初始化时设置的电平状态，输出时有效 0：低电平 1：高电平 仅在设置为输出模式时有效
// 参数说明     mode        引脚的模式 (可选择范围由 zf_driver_gpio.h 内 gpio_mode_enum 枚举值确定)
// 返回参数     void
// 使用示例     gpio_init(D1, GPI, GPIO_HIGH, GPI_PULL_UP);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void gpio_init (gpio_pin_enum pin, gpio_dir_enum dir, const uint8 dat, gpio_mode_enum mode)
{
    uint32 temp = 0;
    uint8 io_group = ((pin & 0xE0) >> 5);                                       // 提取IO分组
    uint8 io_pin = (pin & 0x1F);                                                // 提取IO引脚下标

    RCC->AHB1ENR |= (0x00000001 << io_group);                                   // 使能 GPIOx 时钟

    if(dir == GPI)
    {
        if(mode == GPI_PULL_UP)
        {
            gpio_high(pin);                                                     // 初始化电平设置高
        }
        else
        {
            gpio_low(pin);                                                      // 初始化电平设置低
        }
    }
    else
    {
        gpio_set_level(pin, dat);
    }

    if(0x08 > io_pin)                                                           // 低8位引脚
    {
        temp = gpio_group[io_group]->AFRL;
        temp &= ~(0x0000000F << (io_pin * 4));                                  // 清空 AF 复用
        temp |= ((uint32)15 << (io_pin * 4));                                   // AF 复用设置 15 保留
        gpio_group[io_group]->AFRL = temp;

        temp = gpio_group[io_group]->CRL;
        temp &= ~(0x0000000F << (io_pin * 4));                                  // 清空模式
        temp |= (((uint32)dir | (uint32)(mode & 0x0C)) << (io_pin * 4));        // 写入对应模式
        gpio_group[io_group]->CRL = temp;
    }
    else                                                                        // 高8位引脚
    {
        temp = gpio_group[io_group]->AFRH;
        temp &= ~(0x0000000F << ((io_pin - 8) * 4));                            // 清空 AF 复用
        temp |= ((uint32)15 << ((io_pin - 8) * 4));                             // AF 复用设置 15 保留
        gpio_group[io_group]->AFRH = temp;

        temp = gpio_group[io_group]->CRH;
        temp &= ~(0x0000000F << ((io_pin - 8) * 4));                            // 清空模式
        temp |= (((uint32)dir | (uint32)(mode & 0x0C)) << ((io_pin - 8) * 4));  // 写入对应模式
        gpio_group[io_group]->CRH = temp;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     gpio 复用功能初始化 一般是内部调用
// 参数说明     pin         选择的引脚 (可选择范围由 zf_driver_gpio.h 内 gpio_pin_enum 枚举值确定)
// 参数说明     mode        引脚的方向 [GPI/GPIO]
// 参数说明     af          引脚的功能选择 (可选择范围由 zf_driver_gpio.h 内 gpio_af_enum 枚举值确定)
// 参数说明     mode        引脚的模式 (可选择范围由 zf_driver_gpio.h 内 gpio_mode_enum 枚举值确定)
// 返回参数     void
// 使用示例     afio_init(D5, GPO, GPIO_AF0, GPO_AF_PUSH_PULL);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void afio_init (gpio_pin_enum pin, gpio_dir_enum dir, gpio_af_enum af, gpio_mode_enum mode)
{
    uint32 temp = 0;
    uint8 io_group = ((pin & 0xE0) >> 5);                                       // 提取IO分组
    uint8 io_pin = (pin & 0x1F);                                                // 提取IO引脚下标

    RCC->AHB1ENR |= (0x00000001 << io_group);                                   // 使能 GPIOx 时钟

    if(0x08 > io_pin)                                                           // 低8位引脚
    {
        temp = gpio_group[io_group]->AFRL;
        temp &= ~(0x0000000F << (io_pin * 4));                                  // 清空 AF 复用
        temp |= ((uint32)af << (io_pin * 4));                                   // AF 复用设置对应功能
        gpio_group[io_group]->AFRL = temp;

        temp = gpio_group[io_group]->CRL;
        temp &= ~(0x0000000F << (io_pin * 4));                                  // 清空模式
        temp |= (((uint32)dir | (uint32)(mode & 0x0C)) << (io_pin * 4));        // 写入对应模式
        gpio_group[io_group]->CRL = temp;
    }
    else                                                                        // 高8位引脚
    {
        temp = gpio_group[io_group]->AFRH;
        temp &= ~(0x0000000F << ((io_pin - 8) * 4));                            // 清空 AF 复用
        temp |= ((uint32)af << ((io_pin - 8) * 4));                             // AF 复用设置对应功能
        gpio_group[io_group]->AFRH = temp;

        temp = gpio_group[io_group]->CRH;
        temp &= ~(0x0000000F << ((io_pin - 8) * 4));                            // 清空模式
        temp |= (((uint32)dir | (uint32)(mode & 0x0C)) << ((io_pin - 8) * 4));  // 写入对应模式
        gpio_group[io_group]->CRH = temp;
    }
}
