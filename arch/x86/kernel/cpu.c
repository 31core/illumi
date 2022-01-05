#include <arch/x86/cpu.h>
#include <arch/x86/x86_asm.h>
#include <device/interrupt/interrupt.h>

/* 初始化cpu */
void cpu_init(void)
{
	short i;
	for(i = 0; i < 0x2000; i++)
	{
		GDT_set(i, 0, 0, 0);
	}
	GDT_set(1, 0, 0xffffffff, 0x4000 | ACC_CODE | ACC_READ);
	GDT_set(2, 0, 0xffffffff, 0x4000 | ACC_DATA | ACC_WRITE);
	GDTR_load(GDT_ADDR, 0xffff); //加载GDTR寄存器
	for(i = 0; i < 256; i++)
	{
		IDT_set((char)i, 0, 0, 0);
	}
	IDT_set(0x20, (int)asm_interrupt20h, 8, 0x8e);
	IDT_set(0x21, (int)asm_interrupt21h, 8, 0x8e);
	IDTR_load(IDT_ADDR, 0x7ff); //加载IDTR寄存器
}
/* 设置GDT数据 */
void GDT_set(short count, int base, int limit, short access)
{
	struct GDT_data *GDT = (struct GDT_data*)GDT_ADDR;
	GDT += count; //设置GDT地址到地count个GDT处
	/* 大于1MB则置G为1 */
	if(limit > 0xfffff)
	{
		access |= 0x8000;
		limit /= 0x1000;
	}
	GDT->base_high = base >> 24; //取base高8位
	GDT->base_mid = base >> 16 & 0xff; //取base中间8位
	GDT->base_low = base & 0xffff; //取base低16位
	GDT->limit_high = (limit >> 16 & 0x0f) | (access >> 8 & 0xf0);
	GDT->limit_low = limit & 0xffff; //取limit低16位
	GDT->access = access & 0xff; //取access低8位
}
/* 设置IDT数据 */
void IDT_set(char count, int offset, short selector, char access)
{
	struct IDT_data *IDT = (struct IDT_data*)IDT_ADDR;
	IDT += count; //设置IDT地址到地count个IDT处
	IDT->offset_high = offset >> 16; //取offset高16位
	IDT->offset_low = offset & 0xffff; //取offset低16位
	IDT->selector = selector;
	IDT->count = 0;
	IDT->access = access;
}