# spi_master_xfer_dma

本例为spi主机模式下的回环测试，需要将spi的miso和mosi使用杜邦线连接。
主机模式下，spi的nss引脚、mosi引脚和sck引脚配置为复用输出，spi的miso引脚配置为浮空输入。

## 实验流程

+ 配置DMA，设置DMA传输方式等初始化信息。使能NVIC中断，使能DMA中断。
+ 初始化spi主机，设置时钟频率、波特率、传输模式、极性、数据位宽等配置。
+ 使能spi。
+ 主程序循环等待串口接收任意字符。
+ 当串口接收字符后，spi先进行一次dma传输，用于spi tx, 然后在进行一次dma传输，用于spi rx。dma传输标志位将在中断处理函数中被设置为true，主程序循环等待，当标志位为true时打印传输完成提示语句。

## 实验结果
spi_master_xfer_dma example.

spi tx dma done.
spi rx dma done with data: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
spi tx dma done.
spi rx dma done with data: 0 2 4 6 8 10 12 14 0 2 4 6 8 10 12 14