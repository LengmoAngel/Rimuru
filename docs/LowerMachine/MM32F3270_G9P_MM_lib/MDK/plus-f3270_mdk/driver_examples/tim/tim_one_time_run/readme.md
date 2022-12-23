# tim_one_time_run

### 实验流程

- 初始化 BOARD_TIM_PORT ,通过设置 ClockFreqHz 和 StepFreqHz 和 APP_TIM_UPDATE_PERIOD，初始化时基单元，实现定时器周期为 2 s。（ StepFreqHz = ClockSourceFreqHz / (ClockSourceDiv+1)，Clock timing = ( Period + 1 ) / StepFreqHz ）将定时器运行模式设置为 TIM_PeriodMode_OneTimeRun 模式，启动后只执行一次。使能定时器的更新中断，使能定时器。
- 重写定时器的中断处理函数，检查其中断标志位中更新位是否置位1，是则打印 * ，然后清除中断。
- 主函数中每当串口接收到字符，将启动定时器，完成一次 2s 的计时。用户将在 2s 后在串口输出看到 * 。

### 实验结果

tim_one_time_run.
**
