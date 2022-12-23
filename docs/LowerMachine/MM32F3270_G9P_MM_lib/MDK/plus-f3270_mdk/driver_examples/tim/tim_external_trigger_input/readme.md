# tim_external_trigger_input

在此样例中，使用杜邦线将某个按键与ETR引脚相连，模拟输入电平变换，因为按键按下时为低电平，松开时为高电平，可以模拟上下沿输入。

### 实验流程

- 初始化 BOARD_TIM_PORT , 参考 basic 样例中对于时基的初始化,选择递增计数。使能此定时器的更新中断，打开NVIC的中断处理。初始化定时器外部触发输入功能，设置为下降沿触发，不分频不滤波。使能定时器。
- 重写定时器的中断处理函数，在此函数中判断是否是更新中断。如果是，则串口打印更新提示语句。
- 如果指定按键被按下，则外部触发输入捕获一次下降沿，驱动计数器加一。当按下APP_TIM_UPDATE_PERIOD次后，在又一次按下时会触发更新中断，计数值将自动清 0 。
- 主循环中循环等待串口接受输入字符，然后打印当前计数器中的值。

### 实验结果

tim_external_trigger_input.
press input key to trigger external trigger input and lead an update with indicated period.
counter:0
counter:1
timeout event happens.
