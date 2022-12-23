# pff_sdcard_basic

## 实验过程

+ 用户通过串口输入字符，折本根据字符决定装载，读写 SD 卡。

## 实验结果

petit_fatfs_basic.
pf_mount().
done.

pf_opendir() & pf_readdir().
   <dir>  SYSTEM~1
   <dir>  DIR0
   <dir>  DIR1
       0  FIL0.TXT
       0  FIL1.TXT
done.

pf_open() & pf_write().
pf_open()
fail. 3
pf_open() & pf_read().
pf_open().
fail. 3

a: f_mount().
b: pf_opendir() & pf_readdir().
c: pf_open() & pf_write().
d: pf_open() & pf_read().