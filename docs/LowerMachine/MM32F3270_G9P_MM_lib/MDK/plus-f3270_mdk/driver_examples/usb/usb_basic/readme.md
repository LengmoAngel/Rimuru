# usb_basic

## 实验过程

+ 初始化 usb ，将512字节对齐的缓冲区描述符地址传给 usb 。
+ 使能中断，打开 USB_INT_RESET 、 USB_INT_TOKENDONE 、 USB_INT_STALL 中断。
+ 通过中断进入并处理相应的中断，并在中断中实现数据传输，完成枚举过程。

## 实验结果

电脑USB连接设备，一到两秒后通过设备管理器可查看到枚举出MindMotion字样的鼠标。