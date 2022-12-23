# coremark_baisc

## 实验过程

+ coremark_basic样例的main.c文件处于屏蔽状态，样例中所使用的main()函数处于coremark_main.c中。
+ 配置TOTAL_DATA_SIZE为1200，迭代次数为12000次。
+ 通过串口打印coremark的迭代次数、运行时间、每秒迭代次数等信息。

## 实验结果

Profile generation run parameters for coremark.
CoreMark Size    : 400
Total ticks      : 38377
Total time (secs): 38.377000
Iterations/Sec   : 312.687287
Iterations       : 12000
Compiler version : GCC 10.3.1
Compiler flags   : -0hs -no_size_constraints
Memory location  : STACK
seedcrc          : 0x4eaf
[0]crclist       : 0x6a79
[0]crcmatrix     : 0x5608
[0]crcstate      : 0xe5a4
[0]crcfinal      : 0x8d4c
Correct operation validated. See README.md for run and reporting rules.
done.