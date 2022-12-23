# dac_dual

## 实验过程

+ 初始化 DAC 通道 1 为软件触发，设置 DAC 输出三角波，使能 DAC 通道 1。使能 DAC 通道 1。以相同方式配置 DAC 通道 2 。 向通道 1 和通道 2 以 12 比特右对齐方式放入三角波的基值为 256u 并进行软件触发将数立即写入对应通道，主函数进入循环等待。
+ 当串口收到任意字符时，分别读出通道 1 和通道 2 的输出值，使用串口打印。
+ 进行软件触发，通道 1 和通道 2 的值会增加 1u。等待下一次串口接受到字符。

## 实验结果

dac_dual example.
DAC dual outputs :256 and 256.
DAC dual outputs :257 and 257.
DAC dual outputs :258 and 258.
DAC dual outputs :259 and 259.
DAC dual outputs :260 and 260.
DAC dual outputs :261 and 261.
DAC dual outputs :262 and 262.
DAC dual outputs :263 and 263.
DAC dual outputs :264 and 264.
DAC dual outputs :265 and 265.
DAC dual outputs :266 and 266.
DAC dual outputs :267 and 267.
DAC dual outputs :268 and 268.
DAC dual outputs :269 and 269.