# tim_slave_mode_encoder

使用 定时器 的 通道 1 进行输入捕获，需要将其初始化为复用浮空输入。 通道 2 做同样设置。
在此样例中，使用杜邦线将 通道 1 引脚 与 一个IO引脚 相连，将 通道 2 引脚  与 另一个引脚 相连，设置推挽输出，用于模拟正交信号输入。

### 实验流程

- 初始化 BOARD_TIM_PORT , 参考 basic 样例中对于时基的初始化,选择递增计数。使能此定时器的更新中断，以及打开NVIC的中断处理。初始化通道 1 和通道 2 的输入捕获功能，针对上升沿进行捕获，不进行分频和滤波。初始化定时器从模式控制，选择编码器模式3，使能定时器。
- 重写定时器的中断处理函数，在此函数中判断是否是更新终端，如果是则串口打印 update 。
- 主循环中循环一个周期的模拟正交信号，等待串口接收字符，然后打印当前编码器的方向以及计数值。此样例中计数值应为此正交波形中双通道上的上升和下脉冲总数。

### 实验结果

tim_slave_mode_encoder.
moving direction is forward with pulse times:4.
moving direction is forward with pulse times:8.
moving direction is forward with pulse times:12.
