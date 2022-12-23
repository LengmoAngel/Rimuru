# i2c_master_basic

## 实验流程

+ 初始化 i2c 主机，设置时钟频率和波特率，设置目标设备地址，使能 i2c。
+ 主程序中循环等待串口键入任意字符。
+ 当串口接收到字符后，i2c 写准备的数组，并打印写操作结果。
+ 写操作中，第一个写入的数据被算作设备寄存器地址。
+ 当串口再一次接收到字符时，i2c 读数，并打印读操作结果。

## 实验结果

i2c_master_basic example
press any key to write i2c-eeprom.
write data: 0x00, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
press any key to read i2c-eeprom.
read data from device register address: 0x00
read data:  0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
press any key to write i2c-eeprom.
write data: 0x00, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
press any key to read i2c-eeprom.
read data from device register address: 0x00
read data:  0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,