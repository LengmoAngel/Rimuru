# comp_extvref

## 实验过程

+ 初始化 comp 实例，配置输出滤波器，输出将不翻转，比较器输出不定向到任何定时，配置正向输入通道和反向输入通道的输入源，设置高速比较模式。
+ 使能 comp 实例。
+ 使能 comp 的 ext Vref 功能，设置外部参考电压为 50% 的 VDDA。

+ 主程序中，用户根据提示向串口输入任意字符。串口打印输出比较器COMP的正向输入通道1的输入电压与外部参考电压的比较结果。

## 实验结果

COMP Ext Vref.
Press any key to get compare result.
Positive Input Higher.
Positive Input Higher.
