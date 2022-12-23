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
* 文件名称          zf_driver_sdio
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
#include "hal_sdio.h"
#include "zf_common_clock.h"
#include "zf_driver_gpio.h"
#include "zf_driver_delay.h"

#include "zf_driver_sdio.h"

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     sdio 获取当前状态
// 参数说明     cmd_index       命令索引
// 参数说明     param           参数
// 参数说明     flags           标志
// 返回参数     void
// 使用示例                     sdio_get_state();
//-------------------------------------------------------------------------------------------------------------------
uint32 sdio_get_state (void)
{
    uint32 flags = SDIO->CLRMMCINT;

    if (SDIO->BUFCTL & 0x00000001)
    {
        flags |= 0x00000200;
    }
    if (SDIO->BUFCTL & 0x00000002)
    {
        flags |= 0x00000400;
    }

    return flags;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     sdio 清除当前状态
// 参数说明     flags           对应状态
// 返回参数     void
// 使用示例                     sdio_clear_state(0x00000009);
//-------------------------------------------------------------------------------------------------------------------
void sdio_clear_state (uint32 flags)
{
    SDIO->CLRMMCINT = (0x000000FF & flags);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     sdio 执行命令
// 参数说明     cmd_index       命令索引
// 参数说明     param           参数
// 参数说明     flags           标志
// 返回参数     void
// 使用示例                     sdio_execute_cmd(0, 0, 0);
//-------------------------------------------------------------------------------------------------------------------
sdio_error_state_enum sdio_execute_cmd (uint8 cmd_index, uint32 param, uint32 flags)
{
    uint32 cmd_io = 0;
    uint32 cmd_io_ext = 0;
    uint32 timeout_count = 0;
    sdio_error_state_enum return_state = SDIO_ERROR_STATE_NO_ERROR;

    do
    {
        SDIO->CMDBUF[4] = 0x40 | cmd_index;
        SDIO->CMDBUF[3] = ((param & 0xff000000) >> 24);
        SDIO->CMDBUF[2] = ((param & 0xff0000  ) >> 16);
        SDIO->CMDBUF[1] = ((param & 0xff00    ) >> 8);
        SDIO->CMDBUF[0] = ( param & 0xff      );

        cmd_io          = 0x00000004;
        cmd_io_ext      = SDIO->MMCIOMBCTL;
        cmd_io_ext     &= 0xFFFFFFF8;

        if (0u != (flags & 0x00000040))
        {
            cmd_io_ext |= 0x00000002;
            SDIO->MMCIO = 0u;
            SDIO->MMCIOMBCTL = cmd_io_ext | 0x00000001;
        }
        else
        {
            if (0u != (flags & 0x00000001) )
            {
                cmd_io |= 0x00000002;
            }
            if (0u != (flags & 0x00000004) )
            {
                cmd_io |= 0x00000010;
            }
            if (0u != (flags & 0x00000080) )
            {
                cmd_io |= 0x00000001;
            }
            SDIO->MMCIOMBCTL = cmd_io_ext;
            SDIO->MMCIO = cmd_io;
        }

        while (0u == (0x00000001 & sdio_get_state()))
        {
            timeout_count ++;
            if(SDIO_TIMEOUT_COUNT < timeout_count)
            {
                return_state = SDIO_ERROR_STATE_TIME_OUT;
                break;
            }
            system_delay_ms(1);
        }
        if(SDIO_ERROR_STATE_TIME_OUT == return_state)
        {
            break;
        }
        sdio_clear_state(0x00000001);
    }while(0);
    return SDIO_ERROR_STATE_NO_ERROR;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     sdio 更新数据
// 参数说明     data            数据
// 返回参数     void
// 使用示例                     sdio_execute_data(0x00000001);
//-------------------------------------------------------------------------------------------------------------------
void sdio_execute_data (uint32 data)
{
    uint32 cmd_io = 0u;
    uint32 cmd_io_ext = SDIO->MMCIOMBCTL;

    cmd_io_ext &= 0xFFFFFFF8;

    if(0u != (data & 0x00000002) )
    {
        cmd_io |= 0x00000001;
    }
    if(0u != (data & 0x00000001) )
    {
        cmd_io |= 0x00000003;
    }
    if(0u != (data & 0x00000020) )
    {
        cmd_io_ext |= 0x000000001;
    }
    else if(0u != (data & 0x00000040) )
    {
        cmd_io_ext |= 0x000000003;
    }

    SDIO->MMCIO = cmd_io;
    SDIO->MMCIOMBCTL = cmd_io_ext;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     sdio 请求响应
// 参数说明     type            响应类型
// 参数说明     *resp           响应缓冲区 可以设置为 NULL 忽略数据
// 返回参数     void
// 使用示例                     sdio_request_resp(SDIO_RESP_TYPE_R1, NULL);
//-------------------------------------------------------------------------------------------------------------------
sdio_error_state_enum sdio_request_resp (sdio_resp_type_enum type, uint32 *resp)
{
    uint32 cmd_io = 0x0000000C;
    uint32 timeout_count = 0;
    sdio_error_state_enum return_state = SDIO_ERROR_STATE_NO_ERROR;

    do
    { 
        if (type == SDIO_RESP_TYPE_R2)
        {
            cmd_io |= 0x00000010;
        }
        SDIO->MMCIO = cmd_io;

        while (0u == (0x00000001 & sdio_get_state()))
        {
            timeout_count ++;
            if(SDIO_TIMEOUT_COUNT < timeout_count)
            {
                return_state = SDIO_ERROR_STATE_TIME_OUT;
                break;
            }
            system_delay_ms(1);
        }
        if(SDIO_ERROR_STATE_TIME_OUT == return_state)
        {
            break;
        }
        sdio_clear_state(0x00000009);

        uint32 buf[4];
        buf[0] = (SDIO->CMDBUF[3] << 24)
              | (SDIO->CMDBUF[2] << 16)
              | (SDIO->CMDBUF[1] << 8 )
              | (SDIO->CMDBUF[0]);

        if (type == SDIO_RESP_TYPE_R2)
        {
            buf[1] = (SDIO->CMDBUF[7] << 24)
                  | (SDIO->CMDBUF[6] << 16)
                  | (SDIO->CMDBUF[5] << 8 )
                  | (SDIO->CMDBUF[4]);
            buf[2] = (SDIO->CMDBUF[11] << 24)
                  | (SDIO->CMDBUF[10] << 16)
                  | (SDIO->CMDBUF[9 ] << 8 )
                  | (SDIO->CMDBUF[8 ]);
            buf[3] = (SDIO->CMDBUF[15] << 24)
                  | (SDIO->CMDBUF[14] << 16)
                  | (SDIO->CMDBUF[13] << 8 )
                  | (SDIO->CMDBUF[12]);
        }
        if(NULL != resp)
        {
            memcpy(resp, buf, sizeof(buf));
        }
    }while(0);
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     sdio 设置数据总线位宽
// 参数说明     width           数据总线位宽
// 返回参数     void
// 使用示例                     sdio_set_data_bus_width(SDIO_DATA_BUS_1BIT);
//-------------------------------------------------------------------------------------------------------------------
void sdio_set_data_bus_width (sdio_data_bus_width_enum width)
{
    if(SDIO_DATA_BUS_4BIT == width)
    {
        SDIO->MMCCTRL |= 0x00000080;
    }
    else
    {
        SDIO->MMCCTRL &= 0xFFFFFF7F;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     sdio 失能
// 参数说明     void
// 返回参数     void
// 使用示例                     sdio_disable();
//-------------------------------------------------------------------------------------------------------------------
void sdio_disable (void)
{
    SDIO->MMCCARDSEL &= 0xFFFFFF3F;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     sdio 使能
// 参数说明     void
// 返回参数     void
// 使用示例                     sdio_enable();
//-------------------------------------------------------------------------------------------------------------------
void sdio_enable (void)
{
    SDIO->MMCCARDSEL |= 0x000000C0;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     sdio 初始化
// 参数说明     void
// 返回参数     void
// 使用示例                     sdio_init();
//-------------------------------------------------------------------------------------------------------------------
void sdio_init (void)
{
    uint32 register_data = 0;

    afio_init(C8 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // SDIO D0  引脚初始化
    afio_init(C9 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // SDIO D1  引脚初始化
    afio_init(C10, GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // SDIO D2  引脚初始化
    afio_init(C11, GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // SDIO D3  引脚初始化
    afio_init(C12, GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // SDIO CLK 引脚初始化
    afio_init(D2 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // SDIO CMD 引脚初始化

    system_delay_ms(100);

    RCC->AHB1ENR |= (0x00000400);                                               // 使能 SDIO 时钟
    RCC->AHB1RSTR |= (0x00000400);                                              // 复位 SDIO 外设
    RCC->AHB1RSTR &= (0xFFFFFBFF);                                              // 复位 结束

    sdio_enable();

    register_data = SDIO->MMCCTRL;
    register_data |= 0x00000001;                                                // 切换 SDIO 接口到 SD/MMC/SDIO 模式
    register_data |= 0x00000002;                                                // 切换 SDIO 接口到 SD/MMC/SDIO 端口自动传输模式
    register_data &= 0xFFFFFFFB;                                                // CMD 控制模式选择 推挽输出
    register_data = ((register_data & 0xFFFFFFC7) | 0x00000010);                // CLK 时钟速率选择 基准时钟六分频
    register_data |= 0x00000040;                                                // SD/MMC/SDIO 端口高速传输模式 即时钟源为 AHB 时钟
    register_data &= 0xFFFFFF7F;                                                // SD/MMC/SDIO 端口 1bit 总线宽度
    register_data &= 0xFFFFF8FF;                                                // SD/MMC 模式 SDIO 中断禁止 SDIO 读等待禁用
    SDIO->MMCCTRL = register_data;

    SDIO->MMCCRCCTL = 0x00000000;                                               // 禁止所有 CRC 操作
    SDIO->MMCIOMBCTL = 0x00000000;                                              // 禁用自动多块传输
                                                                                // 数据方向写入
                                                                                // 禁用全自动命令和多块数据
                                                                                // CLK极性默认
                                                                                // 禁用超时选择
    SDIO->MMCCRCCTL |= 0x000000C0;                                              // 启用 CMD 和 DAT 线路的 CRC 电路使能
}
