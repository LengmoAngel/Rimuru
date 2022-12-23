# tud_compose_cdc_msc_ramdisk

## 实验过程

+ 初始化 TinyUSB 实例。
+ 循环处理 cdc 任务。

## 实验结果

串口无打印内容。
USB 接入主机后枚举出串口和存储器，串口可回环用户输入的任意字符串，存储器内有 readme.txt 文件。