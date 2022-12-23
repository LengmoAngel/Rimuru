# dac_basic

## 实验过程

+ 初始化 DAC 通道 2 为无触发源，并使能 DAC ，主函数进入循环等待。
+ 当串口收到任意字符时，更新设定值（设定值从 0 开始以 128 步长递增到 3968 ）。
+ 向DAC通道 2 以 12 比特右对齐方式放入设定值。
+ 读出 DAC 通道 2 输出值并保存。
+ 使用串口打印输出值，打印完毕后等待下一次串口收到字符。

## 实验结果

dac_basic example.
DAC output is : 128.
DAC output is : 256.
DAC output is : 384.
DAC output is : 512.
DAC output is : 640.
DAC output is : 768.
DAC output is : 896.
DAC output is : 1024.
DAC output is : 1152.
DAC output is : 1280.
DAC output is : 1408.