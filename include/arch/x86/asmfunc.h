void GDTR_load(int, int); //加载GDRT寄存器
void IDTR_load(int, int);
void io_out8(int, int);
int io_in8(int);
void io_out16(int, int);
int io_in16(int);
void io_cli();
void io_sti();
