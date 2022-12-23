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
* 文件名称          zf_driver_adc
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
#include "zf_driver_gpio.h"

#include "zf_driver_adc.h"

static  ADC_Type    *adc_index[3]       = {ADC1, ADC2, ADC3};
static  uint8       adc_resolution[3]   = {ADC_12BIT, ADC_12BIT, ADC_12BIT};

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     adc 转换一次
// 参数说明     ch              选择 adc 通道 (详见 zf_driver_adc.h 中枚举 adc_channel_enum 定义)
// 返回参数     uint16          转换的 adc 值
// 使用示例     adc_convert(ADC1_CH0_A0);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint16 adc_convert (adc_channel_enum ch)
{
    uint8 adc = ((ch & 0xF000) >> 12);
    adc_index[adc]->ADCHS = (0x00000001 << ((ch & 0xF00) >> 8));                // 使能对应通道
    adc_index[adc]->ADCR |= (0x00000001 << 8);                                  // 开始数据转换
    while(0 == ((adc_index[adc]->ADSTA ) & (0x00000001)));                      // 等待数据转换完成
    adc_index[adc]->ADSTA |= (0x00000001);                                      // 清除转换完成标志
    return ((adc_index[adc]->ADDATA & 0xFFF) >> adc_resolution[adc]);           // 读取数据
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     adc 均值滤波转换
// 参数说明     ch              选择 adc 通道 (详见 zf_driver_adc.h 中枚举 adc_channel_enum 定义)
// 参数说明     count           均值滤波次数
// 返回参数     uint16          转换的 adc 值
// 使用示例     adc_mean_filter_convert(ADC1_CH0_A0, 5);                        // 采集5次 然后返回平均值
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint16 adc_mean_filter_convert (adc_channel_enum ch, const uint8 count)
{
    uint8 i = 0;
    uint32 sum = 0;

    for(i = 0; i < count; i ++)
    {
        sum += adc_convert(ch);
    }

    return (sum / count);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     adc 初始化
// 参数说明     ch              选择 adc 通道 (详见 zf_driver_adc.h 中枚举 adc_channel_enum 定义)
// 参数说明     resolution      选择选择通道分辨率(如果同一个 adc 模块初始化时设置了不同的分辨率 则最后一个初始化的分辨率生效)
// 返回参数     void
// 使用示例     adc_init(ADC1_CH0_A0, ADC_8BIT);                                // 初始化 A0 为 ADC1 的 channel0 输入功能 分辨率为8位
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void adc_init (adc_channel_enum ch, adc_resolution_enum resolution)
{
    uint8 adc = ((ch & 0xF000) >> 12);
    uint32 adcfg_temp = 0;
    uint32 adcr_temp = 0;

    if((0xF00 == (ch & 0xF00)) && (0xE00 == (ch & 0xF00)))                      // 确认是引脚通道
    {
        gpio_init((gpio_pin_enum)(ch & 0xFF), GPI, GPIO_LOW, GPI_ANAOG_IN);
    }

    RCC->APB2ENR |= (0x00000100 << adc);                                        // 使能 ADC 时钟
    RCC->APB2RSTR |= (0x00000100 << adc);                                       // 复位 ADC 外设
    RCC->APB2RSTR &= ~(0x00000100 << adc);                                      // 复位 结束

    adcfg_temp = adc_index[adc]->ADCFG;
    adcr_temp = adc_index[adc]->ADCR;

    if(0 == adc && (0xF00 == (ch & 0xF00)))                                     // 如果是 ADC1 的通道15 内部参考电压
    {
        adcfg_temp |= (0x00000001 << 3);                                        // 开启内部电压传感器使能
    }

    if(0 == adc && (0xE00 == (ch & 0xF00)))                                     // 如果是 ADC1 的通道14 内部温度传感器
    {
        adcfg_temp |= (0x00000001 << 2);                                        // 开启温度传感器使能
    }

    adc_resolution[adc] = resolution;                                           // 记录ADC精度 将在采集时使用 详细请查看 UM <12.5.1 可编程分辨率> 章节
    adcfg_temp |= ((uint32)resolution << 7);                                    // ADC 精度修改
    adcfg_temp |= (0x00000003<<4);                                              // ADC 时钟 8 分频
    adcr_temp &= ~(0x00000E00);                                                 // 清空设置 默认单次转换 数据右对齐
    adcr_temp |= (0x00000001<<9);                                               // 单周期转换
    adcfg_temp |= (0x00000001);                                                 // ADC 使能

    adc_index[adc]->ADCR = adcr_temp;
    adc_index[adc]->ADCFG = adcfg_temp;
}
