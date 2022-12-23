# iwdg driver examples

# iwdg_basic

## 实验流程

+ 初始化 BOARD_WWDG_PORT ，配置预分频系数（Prescaler），配置重装载计数器转载值。
+ 启动窗口看门狗，重装载计数器10次数。
+ 主程序打印重装载计数器操作次数提示语句10次，然后进入死循环，等待MCU复位。

## 实验结果

iwdg_basic example.
Feed dog count: 1
Feed dog count: 2
Feed dog count: 3
Feed dog count: 4
Feed dog count: 5
Feed dog count: 6
Feed dog count: 7
Feed dog count: 8
Feed dog count: 9
Feed dog count: 10
iwdg_basic example.
Feed dog count: 1
Feed dog count: 2
Feed dog count: 3
Feed dog count: 4
Feed dog count: 5
Feed dog count: 6
Feed dog count: 7
Feed dog count: 8
Feed dog count: 9
Feed dog count: 10