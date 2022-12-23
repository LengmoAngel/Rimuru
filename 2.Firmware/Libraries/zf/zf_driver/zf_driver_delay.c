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
* 文件名称          zf_driver_delay
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

#include "zf_driver_delay.h"

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     system 延时函数
// 参数说明     time			需要延时的时间
// 参数说明     num			    需要延时的次数
// 返回参数     void
// 使用示例     system_delay(1000000, (time));
// 备注信息     无需用户调用 用户请使用 zf_driver_delay.h 文件中的宏定义
//-------------------------------------------------------------------------------------------------------------------
void system_delay (uint32 time, uint32 num)
{
	while(num --)
	{
		SysTick->CTRL	= 0x00;
		SysTick->LOAD	= (system_clock / 1000000 * time / 1000);
		SysTick->VAL	= 0x00;
		SysTick->CTRL	=	SysTick_CTRL_CLKSOURCE_Msk |                        // 时钟源选择 (core clk)
							SysTick_CTRL_ENABLE_Msk;                            // 使能 systick
		while( !(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
	}
}
