# rtc_interrupt

## 实验过程

+ 初始化 RTC 实例。
+ 等待 RTC 时钟准备完成。
+ 使能 RTC 实例。
+ 等待 RTC 同步完成。
+ 打开 RTC 中断。
+ 通过串口读取用户输入的字符，根据字符打印当前时间或重新初始化 RTC 。

## 实验结果

RTC interrupt example.
Press key 'a' to initialize rtc, 'b' to get current time, 'c' to use alarm clock.
a: app_rtc_init().
RTC init succeed.
2008-12-31 23:59:14
b: app_rtc_get_interrupt_current_time().
2008-12-31 23:59:15
c: app_rtc_alarm_interrupt().
current time is 2008-12-31 23:59:17
alarm response: 2008-12-31 23:59:18
a: app_rtc_init().
b: app_rtc_get_interrupt_current_time().
c: app_rtc_alarm_interrupt().