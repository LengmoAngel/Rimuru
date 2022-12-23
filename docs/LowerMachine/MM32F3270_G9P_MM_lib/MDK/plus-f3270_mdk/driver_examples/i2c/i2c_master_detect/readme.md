# i2c_master_detect

## 实验流程

+ 初始化 i2c 主机，设置时钟频率和波特率，设置目标设备地址，使能 i2c。
+ 主程序中循环等待串口键入任意字符。
+ 当串口接收到字符后，i2c 进行检测。将检测地址从0x0到0xFE的偶数目标地址。通过发送报文，检查报文是否发送成功的方式得到地址是否有效。

## 实验结果

i2c_master_detect example.
press any key to detect I2C.
target: 0x00, device not exists.
target: 0x02, device not exists.
target: 0x04, device not exists.
			.
			.
			.
target: 0x9C, device not exists.
target: 0x9E, device not exists.
target: 0xA0, device exists.
target: 0xA2, device not exists.
target: 0xA4, device not exists.
			.
			.
			.
target: 0xFE, device not exists.