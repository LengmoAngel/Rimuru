# tud_compose_cdc_msc_sdcard

## 实验过程

+ 初始化 SD 卡实例
+ 初始化 TinyUSB 实例。
+ 循环处理 cdc 任务。

## 实验结果

USB 接入主机后枚举出串口和存储器，串口可回环用户输入的任意字符串，存储器为 SD 卡，显示出 SD 内的文件。

tinyusb_msc_sdcard.
sdcard_init() done.