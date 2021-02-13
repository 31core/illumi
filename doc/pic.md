### 1.PIC简介
可编程中断控制器(programmable  interrupt  controller,PIC)。PIC可以接受外部设备的中断信号，并通知CPU。
### 2.PIC初始化
中断屏蔽寄存器(interrupt mask register,IMR),可以写入8位数据，每一为对应一个IRQ，置1则屏蔽中断。(主PIC 0xa1,从PIC0x21)<br>

先向ICW1(主PIC 0xa0,从PIC0x20)写入8位数据，再依次写入ICW2、ICW3、ICW4(主PIC 0xa1,从PIC0x21)
### PIC中断
* IRQ1 : 键盘中断。