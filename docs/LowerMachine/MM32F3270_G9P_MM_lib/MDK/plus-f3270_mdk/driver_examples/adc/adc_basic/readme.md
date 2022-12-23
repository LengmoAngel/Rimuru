# adc_awdg

## 实验过程

+ 初始化 adc 实例，配置精度12b，时钟16分频，运行在 conversion by sequence 模式下，右对齐。
+ 使能 adc 转换序列。
+ 使能 adc 实例。
+ 主函数中，用户根据提示向串口输入任意字符，adc 开始转换比较结果，串口打印结果。

## 实验结果

adc_basic example.
press any key to start the conversion.
app_run_conv() start...
adc_val= 1846
app_run_conv() done.
