# tim_comp_output_compare_pwm

### 实验流程

- 初始化 BOARD_TIM_PORT , 参考 basic 样例中对于时基的初始化,选择递增计数。初始化通道1的输出比较模式，比较值初始化为0，选择TIM_ADV_OutputCompareRefOut_FallingEdgeOnMatch比较输出模式，匹配前为高电平，匹配后为低电平。
- 使能定时器。
- 主函数中每当串口接收到字符，将预先计算好的 12.5% 至 100% (步长 12.5% )的占空比对应的比较值放入通道中，以实现每次键入都可观察到不同的占空比下的波形。其中互补通道 电平正好与通道电平相反。

### 实验结果

tim_comp_output_compare_pwm.
PWM value: 125
PWM value: 250
PWM value: 375
PWM value: 500
PWM value: 625
PWM value: 750
PWM value: 875
PWM value: 1000
