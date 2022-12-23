# tim_input_capture

在此样例中，使用杜邦线将指定按键与定时器输入通道引脚相连，模拟输入电平变换，因为按键按下时为低电平，松开时为高电平，可以模拟上下沿输入。按键需配置为上拉输入。

### 实验流程

- 初始化 BOARD_TIM_PORT , 参考 basic 样例中对于时基的初始化,选择递增计数。使能此定时器的通道1中断，以及打开NVIC的中断处理。初始化通道的输入捕获功能，针对下降沿进行捕获，不进行分频和滤波。使能定时器。
- 重写定时器的中断处理函数，在此函数中检查此定时器的 通道事件中断位是否为 1 ，如果是则说明有补获事件发生，将全局标志位app_tim_event_on设为真，然后清除通道 1 的事件中断位。
- 主函数中轮询app_tim_event_on位，检查是否为真，为真则将其清为假，然后串口打印输出捕获时间。继续轮询，等待下次输入捕获时间发生。

### 实验结果

tim_input_capture.
press input key to trigger input capture channel.
tim input capture event.
tim input capture event.
tim input capture event.
tim input capture event.
tim input capture event.
