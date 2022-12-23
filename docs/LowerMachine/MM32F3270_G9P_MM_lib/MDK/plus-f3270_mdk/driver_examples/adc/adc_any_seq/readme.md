# adc_any_seq

## 实验过程

+ 初始化 dma 实例。
+ 初始化 adc 实例，配置精度12b，时钟16分频，运行在 conversion by sequence 模式下，右对齐。
+ 使能 adc 转换序列。
+ 使能 adc 实例。
+ 主函数中，用户根据提示向串口输入任意字符，adc 开始转换，串口打印通道转换值。

## 实验结果

adc_any_seq example.
press any key to start the conversion.
any_seq conversion start...
adc_val[0] = 1845
adc_val[1] = 0
adc_val[2] = 1666
adc_val[3] = 1845
any_seq conversion done.
