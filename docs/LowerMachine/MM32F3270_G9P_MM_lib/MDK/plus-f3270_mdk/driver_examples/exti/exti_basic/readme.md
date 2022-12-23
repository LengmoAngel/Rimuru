# exti_basic

## 实验过程

+ 设置SYSCFG的外部输入引脚线和引脚号。设置EXTI的输入源和输入边沿，使能EXTI的中断。

+ 主程序中不断轮询全局标志位，当 BOARD_EXTI_LINE 的 BOARD_EXTI_PORT 引脚上出现下降沿，触发 exti 中断，进入中断处理函数，将全局标志位设置为真。串口将打印累计的 exti 中断次数。
+ 清空全局标志位，等待下一次事件。

## 实验结果

exti_basic.
exti interrupt times:1.
exti interrupt times:2.
exti interrupt times:3.
exti interrupt times:4.
exti interrupt times:5.
exti interrupt times:6.
