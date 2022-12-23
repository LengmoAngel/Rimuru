# spi_master_basic

本例为spi主机模式下的回环测试，需要将spi的miso和mosi使用杜邦线连接。
主机模式下，spi的nss引脚、mosi引脚和sck引脚配置为复用输出，spi的miso引脚配置为浮空输入。

## 实验流程

+ 初始化spi主机，设置时钟频率、波特率、传输模式、极性、数据位宽等配置。
+ 使能spi。
+ 主程序循环等待串口接收任意字符。
+ 当串口接收字符后，spi经过APP_SPI_BUFF_LEN次发送-接收。
+ 主循环对接收信息和发送信息进行验证，并打印传输情况。如果有验证失败数据，打印出错信息和出错个数；如果验证成功，打印传输完成的提示语句。

## 实验结果
spi_master_basic example.
spi loopback xfer done.
spi loopback xfer done.