# dac_dma

## 实验过程

+ 初始化 DAC 通道 1 为软件触发，并使能 DAC 通道 1 的 DMA。初始化 DAC 通道 1 对应的 DMA2，使能 DAC 通道 1 对应的 DMA2 通道 3 的中断处理函数。使能 DAC 通道 1 。主函数进入循环等待。
+ 当串口收到任意字符时，实施一次软件触发，DMA 将从指定数组 app_dac_buff_from 以 12 比特右对齐方式传数到DAC 通道 1。
+ 当完成 APP_DAC_BUFF_COUNT 次软件触发后，进入BOARD_DMA_DAC_IRQHandler中断处理函数， 将标记 app_dma_xfer_done 位设为真，并清除 DMA 中断标记位。
+ 主循环每次轮询 app_dma_xfer_done ，为真时打印 DMA 传输完成语句，并将 app_dma_xfer_done 清除， 然后再次开启 DMA 传数。

## 实验结果

dac_dma example.
DAC transfers one data.
DAC transfers one data.
DAC transfers one data.
DAC transfers one data.
DAC transfers one data.
DAC transfers one data.
DAC transfers one data.
DAC transfers one data.
DAC transfers one data.
DAC transfers one data.
DAC transfers one data.
DAC transfers one data.
DAC transfers one data.
DMA transfer finished.
DAC transfers one data.