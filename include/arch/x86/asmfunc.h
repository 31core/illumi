void LoadGDTR(int,int);//加载GDRT寄存器
void LoadIDTR(int,int);//加载IDRT寄存器
void io_out8(int,int);//写8位端口
int io_in8(int);//写8位端口读
void io_out16(int,int);//写16位端口
int io_in16(int);//写16位端口读
void io_cli();//禁用中断
void io_sti();//启用中断

void RecordTaskStatus();
void RestoreTaskStatus();