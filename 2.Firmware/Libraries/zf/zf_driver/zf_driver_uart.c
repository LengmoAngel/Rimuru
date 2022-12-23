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
* 文件名称          zf_driver_uart
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
#include "zf_driver_gpio.h"

#include "zf_driver_uart.h"

static  UART_Type  *uart_index[8]           = {UART1, UART2, UART3, UART4, UART5, UART6, UART7, UART8};
static  IRQn_Type   uart_irq[8]             = {UART1_IRQn, UART2_IRQn, UART3_IRQn, UART4_IRQn, UART5_IRQn, UART6_IRQn, UART7_IRQn, UART8_IRQn};
static  uint8       uart_interrupt_state[8] = {0, 0, 0, 0, 0, 0, 0, 0};

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     串口字节输出
// 参数说明     uart_n          串口模块号 参照 zf_driver_uart.h 内 uart_index_enum 枚举体定义
// 参数说明     dat             需要发送的字节
// 返回参数     void        
// 使用示例     uart_write_byte(UART_1, 0xA5);                                  // 串口1发送0xA5
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void uart_write_byte (uart_index_enum uart_n, const uint8 dat)
{
    uart_index[uart_n]->TDR = dat;                                              // 写入发送数据
    while(!(uart_index[uart_n]->CSR & (0x00000001)));                           // 等待发送完成
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     串口发送数组
// 参数说明     uart_n          串口模块号 参照 zf_driver_uart.h 内 uart_index_enum 枚举体定义
// 参数说明     *buff           要发送的数组地址
// 参数说明     len             发送长度
// 返回参数     void
// 使用示例     uart_write_buffer(UART_1, &a[0], 5);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void uart_write_buffer (uart_index_enum uart_n, const uint8 *buff, uint32 len)
{
    zf_assert(buff != NULL);
    while(len)                                                                  // 循环到发送完
    {
        uart_index[uart_n]->TDR = *buff ++;                                     // 写入发送数据
        while(!(uart_index[uart_n]->CSR & (0x00000001)));                       // 等待发送完成
        len --;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     串口发送字符串
// 参数说明     uart_n          串口模块号 参照 zf_driver_uart.h 内 uart_index_enum 枚举体定义
// 参数说明     *str            要发送的字符串地址
// 返回参数     void
// 使用示例     uart_write_string(UART_1, "seekfree"); 
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void uart_write_string (uart_index_enum uart_n, const char *str)
{
    zf_assert(str != NULL);
    while(*str)                                                                 // 一直循环到结尾
    {
        uart_write_byte(uart_n, *str ++);                                       // 发送数据
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     读取串口接收的数据（whlie等待）
// 参数说明     uart_n          串口模块号 参照 zf_driver_uart.h 内 uart_index_enum 枚举体定义
// 参数说明     *dat            接收数据的地址
// 返回参数     uint8           接收的数据
// 使用示例     uint8 dat = uart_read_byte(UART_1);                             // 接收 UART_1 数据  存在在 dat 变量里
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint8 uart_read_byte (uart_index_enum uart_n)
{
    while(!(uart_index[uart_n]->CSR & (0x00000002)));                           // 等待读取到一个数据
    return (uint8)uart_index[uart_n]->RDR;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     读取串口接收的数据（查询接收）
// 参数说明     uart_n          串口模块号 参照 zf_driver_uart.h 内 uart_index_enum 枚举体定义
// 参数说明     *dat            接收数据的地址
// 返回参数     uint8           1：接收成功   0：未接收到数据
// 使用示例     uint8 dat; uart_query_byte(UART_1, &dat);                       // 接收 UART_1 数据  存在在 dat 变量里
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint8 uart_query_byte (uart_index_enum uart_n, uint8 *dat)
{
    zf_assert(dat != NULL);
    uint8 return_state = 0;
    if(uart_index[uart_n]->CSR & (0x00000002))                                  // 读取到一个数据
    {
        *dat = (uint8)uart_index[uart_n]->RDR;                                  // 存储一个数据
        return_state = 1;
    }
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     串口发送中断设置
// 参数说明     uart_n           串口模块号
// 参数说明     status          1：打开中断   0：关闭中断
// 返回参数     void        
// 使用示例     uart_tx_interrupt(UART_1, 1);                                   // 打开串口1发送完成中断
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void uart_tx_interrupt (uart_index_enum uart_n, uint32 status)
{
    if(status)
    {
        uart_interrupt_state[uart_n] |= 0x10;
        uart_index[uart_n]->IER |= (0x00000001);                                // 使能发送完成中断
        interrupt_enable(uart_irq[uart_n]);
    }
    else
    {
        uart_interrupt_state[uart_n] &= 0xEF;
        uart_index[uart_n]->IER &= ~(0x00000001);                               // 关闭发送完成中断
        if(0x00 == uart_interrupt_state[uart_n])
        {
            interrupt_disable(uart_irq[uart_n]);
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     串口接收中断设置
// 参数说明     uart_n           串口模块号
// 参数说明     status          1：打开中断   0：关闭中断
// 返回参数     void        
// 使用示例     uart_rx_interrupt(UART_1, 1);                                   // 打开串口1接收完成中断
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void uart_rx_interrupt (uart_index_enum uart_n, uint32 status)
{
    if(status)
    {
        uart_interrupt_state[uart_n] |= 0x01;
        uart_index[uart_n]->IER |= (0x00000002);                                // 使能接收完成中断
        interrupt_enable(uart_irq[uart_n]);
    }
    else
    {
        uart_interrupt_state[uart_n] &= 0xFE;
        uart_index[uart_n]->IER &= ~(0x00000002);                               // 关闭接收完成中断
        if(0x00 == uart_interrupt_state[uart_n])
        {
            interrupt_disable(uart_irq[uart_n]);
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     串口初始化
// 参数说明     uart_n          串口模块号 参照 zf_driver_uart.h 内 uart_index_enum 枚举体定义
// 参数说明     baud            串口波特率
// 参数说明     tx_pin          串口发送引脚 参照 zf_driver_uart.h 内 uart_tx_pin_enum 枚举体定义
// 参数说明     rx_pin          串口接收引脚 参照 zf_driver_uart.h 内 uart_rx_pin_enum 枚举体定义
// 返回参数     void            
// 使用示例     uart_init(UART_1, 115200, UART1_TX_A09, UART1_RX_A10);          // 初始化串口1 波特率115200 发送引脚使用PA09 接收引脚使用PA10
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void uart_init(uart_index_enum uart_n, uint32 baud, uart_tx_pin_enum tx_pin, uart_rx_pin_enum rx_pin)
{
    zf_assert((tx_pin & (uart_n << 12)) == (rx_pin & (uart_n << 12)));          // tx_pin 与 rx_pin 必须与 uart_n 匹配
    afio_init((gpio_pin_enum)(tx_pin & 0xFF), GPO, (gpio_af_enum)((tx_pin & 0xF00) >> 8), GPO_AF_PUSH_PULL);// 提取对应IO索引 AF功能编码
    afio_init((gpio_pin_enum)(rx_pin & 0xFF), GPI, (gpio_af_enum)((rx_pin & 0xF00) >> 8), GPI_FLOATING_IN); // 提取对应IO索引 AF功能编码

    switch(uart_n)
    {
        case UART_1:
            RCC->APB2ENR |= ((uint32)0x00000001 << 4);                          // 使能 UART1 时钟
            RCC->APB2RSTR |= ((uint32)0x00000001 << 4);                         // 复位 UART1
            RCC->APB2RSTR &= ~((uint32)0x00000001 << 4);                        // 取消复位 UART1
            break;
        case UART_2:
            RCC->APB1ENR |= ((uint32)0x00000001 << 17);                         // 使能 UART2 时钟
            RCC->APB1RSTR |= ((uint32)0x00000001 << 17);                        // 复位 UART2
            RCC->APB1RSTR &= ~((uint32)0x00000001 << 17);                       // 完成复位 UART2
            break;
        case UART_3:
            RCC->APB1ENR |= ((uint32)0x00000001 << 18);                         // 使能 UART3 时钟
            RCC->APB1RSTR |= ((uint32)0x00000001 << 18);                        // 复位 UART3
            RCC->APB1RSTR &= ~((uint32)0x00000001 << 18);                       // 完成复位 UART3
            break;
        case UART_4:
            RCC->APB1ENR |= ((uint32)0x00000001 << 19);                         // 使能 UART4 时钟
            RCC->APB1RSTR |= ((uint32)0x00000001 << 19);                        // 复位 UART4
            RCC->APB1RSTR &= ~((uint32)0x00000001 << 19);                       // 完成复位 UART4
            break;
        case UART_5:
            RCC->APB1ENR |= ((uint32)0x00000001 << 20);                         // 使能 UART5 时钟
            RCC->APB1RSTR |= ((uint32)0x00000001 << 20);                        // 复位 UART5
            RCC->APB1RSTR &= ~((uint32)0x00000001 << 20);                       // 完成复位 UART5
            break;
        case UART_6:
            RCC->APB2ENR |= ((uint32)0x00000001 << 5);                          // 使能 UART6 时钟
            RCC->APB2RSTR |= ((uint32)0x00000001 << 5);                         // 复位 UART6
            RCC->APB2RSTR &= ~((uint32)0x00000001 << 5);                        // 完成复位 UART6
            break;
        case UART_7:
            RCC->APB1ENR |= ((uint32)0x00000001 << 30);                         // 使能 UART7 时钟
            RCC->APB1RSTR |= ((uint32)0x00000001 << 30);                        // 复位 UART7
            RCC->APB1RSTR &= ~((uint32)0x00000001 << 30);                       // 完成复位 UART7
            break;
        case UART_8:
            RCC->APB1ENR |= ((uint32)0x00000001 << 31);                         // 使能 UART8 时钟
            RCC->APB1RSTR |= ((uint32)0x00000001 << 31);                        // 复位 UART8
            RCC->APB1RSTR &= ~((uint32)0x00000001 << 31);                       // 完成复位 UART8
            break;
    }

    if(SYSTEM_CLOCK_120M < system_clock)
    {
        uart_index[uart_n]->BRR = (system_clock / 2 / baud) / 16;               // 设置波特率
        uart_index[uart_n]->FRA = (system_clock / 2 / baud) % 16;               // 设置波特率
    }
    else
    {
        uart_index[uart_n]->BRR = (system_clock / baud) / 16;                   // 设置波特率
        uart_index[uart_n]->FRA = (system_clock / baud) % 16;                   // 设置波特率
    }
    uart_index[uart_n]->CCR |= (0x00000003 << 4);                               // 8bits 数据位
    uart_index[uart_n]->GCR |= (0x00000019);                                    // 使能 TX RX UART
}
