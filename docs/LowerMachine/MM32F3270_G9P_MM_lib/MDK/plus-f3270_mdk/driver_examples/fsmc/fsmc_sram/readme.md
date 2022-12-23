# fsmc_sram

## 实验过程

+ 初始化 fsmc ，内存类型SRAM，大小1MB。
+ 使能 fsmc 配置，调整总线波形保持时间，总线宽度。
+ 使能 fsmc 。
+ 根据提示用户通过串口输入任意字符，触发对SRAM的读写。
+ 触发读写后，先对SRAM进行一次全写，再进行一次全读，读写比较得出错误的数量。

## 实验结果

fsmc sram example.
sram 8-bit access succ.
sram 8-bit access succ.
sram 8-bit access succ.