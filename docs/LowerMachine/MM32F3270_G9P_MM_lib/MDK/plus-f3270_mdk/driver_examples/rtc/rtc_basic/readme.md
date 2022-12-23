# rtc_basic

## 实验过程

+ 初始化 RTC 实例。
+ 等待 RTC 时钟准备完成。
+ 使能 RTC 实例。
+ 等待 RTC 同步完成。
+ 通过串口读取用户输入的字符，根据字符打印当前时间或重新初始化 RTC 。

## 实验结果

rtc_basic example.
Press key 'a' to initialize rtc, 'b' to get current time.
a: app_rtc_init().
2008-12-31 23:59:15
b: app_rtc_get_current_time().
2008-12-31 23:59:16