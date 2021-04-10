### 1.PIC简介
可编程中断控制器(programmable  interrupt  controller,PIC).PIC可以接受外部设备的中断信号,并通知CPU.
### 2.PIC初始化
中断屏蔽寄存器(interrupt mask register,IMR),可以写入8位数据.每一位对应一个IRQ.置1则屏蔽中断.(主PIC 0x21,从PIC 0xa1)  
初始化:  
先向ICW1(主PIC 0x20,从PIC 0xa0)写入8位数据,再依次写入ICW2、ICW3、ICW4(主PIC 0x21,从PIC 0xa1),一点要按顺序写入.

#### PIT
PIT(programmable interval timer)用于计时器中断.  
初始化: 向0x43端口写入0x34,0x40端口依次写入中断周期低8位,高8位。

#### PIC中断
|IRQ编号|说明|
|---|---|
|IRQ 0|计时器中断|
|IRQ 1|键盘中断|
|IRQ 2|连接从PIC|

### 3.PIC通知
中断发生后应向中断控制器(主PIC 0x20,从PIC 0xa0)写入一字节的数据(0x60+中断编号).否则此中断不会再次发生.