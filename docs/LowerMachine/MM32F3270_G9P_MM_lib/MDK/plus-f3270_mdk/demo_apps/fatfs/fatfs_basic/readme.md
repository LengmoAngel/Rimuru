# fatfs_basic

## 实验过程

+ 用户通过串口输入字符，折本根据字符决定装载，卸载 SD 卡，读写内容。

## 实验结果

fatfs_basic

a: f_mkfs().
b: f_mount().
c: f_open() & f_write() & f_close().
d: f_open() & f_read() & f_close().
f: f_unlink().