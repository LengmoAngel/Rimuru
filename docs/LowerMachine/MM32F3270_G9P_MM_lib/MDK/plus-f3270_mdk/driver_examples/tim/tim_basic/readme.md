# tim_basic

### 实验流程

- 初始化 BOARD_TIM_PORT ,通过设置 ClockFreqHz 和 StepFreqHz 和 APP_TIM_UPDATE_PERIOD，实现定时器周期为 1 s。（ StepFreqHz = ClockSourceFreqHz / (ClockSourceDiv+1)，Clock timing = ( Period + 1 ) / StepFreqHz ）将定时器运行模式设置为 TIM_PeriodMode_Continuous 模式，将循环计时。使能定时器的更新中断，使能定时器。
- 中断处理函数检查中断标志位中更新位是否置为1，是则打印 * ，然后清除改位中断标志位。将全局标志置为true。
- 主函数中不作任何处理，在初始化后进入死循环。每过 1s ，串口将打印一个 * 。

### 实验结果

tim_basic.
**
