# uart_rx_dma

## 实验流程

+ 初始化DMA，配置传输模式等基本信息。
+ 使能DMA中断，使能NVIC中断，使能DMA通道。
+ 初始化串口，配置时钟频率、波特率、字长、传输模式等信息。
+ 使能串口。
+ 主程序打印提示语句，然后进入死循环。
+ 循环中，检查dma传输标志，此标志将会在串口接收到四个字符后，进入中断处理函数后，被设置为true。如果为true，主程序将会通过串口打印出接收信息。

## 实验结果

uart_rx_dma example.
2021
2022
2022