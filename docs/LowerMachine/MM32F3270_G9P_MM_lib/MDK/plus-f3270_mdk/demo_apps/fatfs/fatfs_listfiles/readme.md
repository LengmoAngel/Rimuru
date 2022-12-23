# fatfs_listfiles

## 实验过程

+ 装载 SD 卡。
+ 显示文件列表。
+ 显示文件大小。

## 实验结果

pp_fatfs_listfiles() example.
f_mount(). succ.
* 1:/ ->
        SYSTEM~1/
        DIR0/
        DIR1/
        FIL0.TXT: 0 B
        FIL1.TXT: 0 B
* 1:/dir0/ ->
        FIL1.TXT: 0 B
        FIL0.TXT: 0 B
* 1:/dir1/ ->
        FIL1.TXT: 0 B
        FIL0.TXT: 0 B
app_fatfs_listfiles() done.