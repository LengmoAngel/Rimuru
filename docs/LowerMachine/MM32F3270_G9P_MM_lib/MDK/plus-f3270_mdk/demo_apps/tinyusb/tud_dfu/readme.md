# tud_hid_keyboard

## 实验过程

+ 初始化 TinyUSB 实例。
+ 循环处理 dfu 任务，接收文件并以十六进制格式打印数据，发送字符串到Host。

## 实验结果

USB 接入主机后，使用 zadig（下载链接：https://zadig.akeo.ie/）安装驱动（仅第一次安装）。

使用 dfu-util（下载链接：http://dfu-util.sourceforge.net/）通过下述命令行，实现上传和下载文件的功能：

-   上传文件到Host：.\dfu-util.exe -d cafe -a 0 -U text.txt

-   下载文件到Device：.\dfu-util.exe -d cafe -a 0 -D text.txt