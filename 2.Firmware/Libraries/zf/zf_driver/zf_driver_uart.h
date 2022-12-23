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

#ifndef _zf_driver_uart_h_
#define _zf_driver_uart_h_

#include "zf_common_typedef.h"

typedef enum                                                                    // 枚举串口引脚 此枚举定义不允许用户修改
{
    // UART 1 TX 引脚
    UART1_TX_A9         = 0x0709,                                               // 0x 0[UART1] 7[AF7] 09[A9]
    UART1_TX_B6         = 0x0726,                                               // 0x 0[UART1] 7[AF7] 26[B6]

    // UART 2 TX 引脚
    UART2_TX_A2         = 0x1702,                                               // 0x 1[UART2] 7[AF7] 02[A2]
    UART2_TX_D5         = 0x1765,                                               // 0x 1[UART2] 7[AF7] 65[D5]

    // UART 3 TX 引脚
    UART3_TX_B10        = 0x272A,                                               // 0x 2[UART3] 7[AF7] 2A[B10]
    UART3_TX_C10        = 0x274A,                                               // 0x 2[UART3] 7[AF7] 4A[C10]
    UART3_TX_D8         = 0x2768,                                               // 0x 2[UART3] 7[AF7] 68[D8]

    // UART 4 TX 引脚
    UART4_TX_A0         = 0x3800,                                               // 0x 3[UART4] 8[AF8] 00[A0]
    UART4_TX_C10        = 0x384A,                                               // 0x 3[UART4] 8[AF8] 4A[C10]

    // UART 5 TX 引脚
    UART5_TX_A4         = 0x4804,                                               // 0x 4[UART5] 8[AF8] 04[A4]
    UART5_TX_C12        = 0x484C,                                               // 0x 4[UART5] 8[AF8] 4C[C12]

    // UART 6 TX 引脚
    UART6_TX_B0         = 0x5820,                                               // 0x 5[UART6] 8[AF8] 20[B0]
    UART6_TX_C6         = 0x5846,                                               // 0x 5[UART6] 8[AF8] 46[C6]

    // UART 7 TX 引脚
    UART7_TX_B6         = 0x6826,                                               // 0x 6[UART7] 8[AF8] 26[B6]
    UART7_TX_E8         = 0x6888,                                               // 0x 6[UART7] 8[AF8] 88[E8]

    // UART 8 TX 引脚
    UART8_TX_D0         = 0x7860,                                               // 0x 7[UART8] 8[AF8] 60[D0]
    UART8_TX_E1         = 0x7881,                                               // 0x 7[UART8] 8[AF8] 81[E1]
}uart_tx_pin_enum;

typedef enum                                                                    // 枚举串口引脚 此枚举定义不允许用户修改
{
    // UART 1 RX 引脚
    UART1_RX_A10        = 0x070A,                                               // 0x 0[UART1] 7[AF7] 0A[A10]
    UART1_RX_B7         = 0x0727,                                               // 0x 0[UART1] 7[AF7] 27[B7]

    // UART 2 RX 引脚
    UART2_RX_A3         = 0x1703,                                               // 0x 1[UART2] 7[AF7] 03[A3]
    UART2_RX_D6         = 0x1766,                                               // 0x 1[UART2] 7[AF7] 66[D6]

    // UART 3 RX 引脚
    UART3_RX_B11        = 0x272B,                                               // 0x 2[UART3] 7[AF7] 2B[B11]
    UART3_RX_C11        = 0x274B,                                               // 0x 2[UART3] 7[AF7] 4B[C11]
    UART3_RX_D9         = 0x2769,                                               // 0x 2[UART3] 7[AF7] 69[D9]

    // UART 4 RX 引脚
    UART4_RX_A1         = 0x3801,                                               // 0x 3[UART4] 8[AF8] 01[A1]
    UART4_RX_C11        = 0x384B,                                               // 0x 3[UART4] 8[AF8] 4B[C11]

    // UART 5 RX 引脚
    UART5_RX_A5         = 0x4805,                                               // 0x 4[UART5] 8[AF8] 05[A5]
    UART5_RX_D2         = 0x4862,                                               // 0x 4[UART5] 8[AF8] 62[D2]

    // UART 6 RX 引脚
    UART6_RX_B1         = 0x5821,                                               // 0x 5[UART6] 8[AF8] 21[B1]
    UART6_RX_C7         = 0x5847,                                               // 0x 5[UART6] 8[AF8] 47[C7]

    // UART 7 RX 引脚
    UART7_RX_B7         = 0x6827,                                               // 0x 6[UART7] 8[AF8] 27[B7]
    UART7_RX_E7         = 0x6887,                                               // 0x 6[UART7] 8[AF8] 87[E7]

    // UART 8 RX 引脚
    UART8_RX_D1         = 0x7861,                                               // 0x 7[UART8] 8[AF8] 61[D1]
    UART8_RX_E0         = 0x7880,                                               // 0x 7[UART8] 8[AF8] 80[E0]
}uart_rx_pin_enum;

typedef enum                                                                    // 枚举串口号 此枚举定义不允许用户修改
{
    UART_1,
    UART_2,
    UART_3,
    UART_4,
    UART_5,
    UART_6,
    UART_7,
    UART_8,
}uart_index_enum;

void    uart_write_byte                     (uart_index_enum uartn, const uint8 dat);
void    uart_write_buffer                   (uart_index_enum uartn, const uint8 *buff, uint32 len);
void    uart_write_string                   (uart_index_enum uartn, const char *str);

uint8   uart_read_byte                      (uart_index_enum uartn);
uint8   uart_query_byte                     (uart_index_enum uartn, uint8 *dat);

void    uart_tx_interrupt                   (uart_index_enum uartn, uint32 status);
void    uart_rx_interrupt                   (uart_index_enum uartn, uint32 status);

void    uart_init                           (uart_index_enum uartn, uint32 baud, uart_tx_pin_enum tx_pin, uart_rx_pin_enum rx_pin);

#ifdef COMPATIBLE_WITH_OLDER_VERSIONS                                           // 兼容旧版本开源库接口名称
#define uart_putchar(uart_n, dat)           (uart_write_byte((uart_n), (dat)))
#define uart_putbuff(uart_n, buff, len)     (uart_write_buffer((uart_n), (buff), (len)))
#define uart_putstr(uart_n, str)            (uart_write_string((uart_n), (str)))

#define uart_getchar(uart_n, dat)           (*(dat) = uart_read_byte((uart_n)))
#define uart_query(uart_n, dat)             (uart_query_byte((uart_n), (dat)))

#define uart_tx_irq(uart_n, status)         (uart_tx_interrupt((uart_n), (status)))
#define uart_rx_irq(uart_n, status)         (uart_rx_interrupt((uart_n), (status)))
#endif

#endif
