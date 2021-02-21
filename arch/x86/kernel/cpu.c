#include<arch/x86/cpu.h>
#include<arch/x86/asmfunc.h>
#include<device/interrupt/interrupt.h>

void init_dsctbl()
{
	short i;
	for(i=0;i<0x2000;i++)
	{
		SetGDT(i,0,0,0);
	}
	SetGDT(1,0,0xffffffff,0x409a);
	SetGDT(2,0,0xffffffff,0x4092);
	LoadGDTR(0xffff,0x270000);//加载GDTR寄存器
	for(i=0;i<256;i++)
	{
		SetIDT((char)i,0,0,0);
	}
	SetIDT(0x21,(int)asm_interrupt21h,8,0x8e);
	LoadIDTR(0x7ff,0x26f800);//加载IDTR寄存器
}
/* 设置GDT数据 */
void SetGDT(short count,int base,int limit,short access)
{
	struct GDT_data *GDT=(struct GDT_data*)GDT_ADDR;
	GDT+=count;//设置GDT地址到地count个GDT处
	/* 大于1MB则置G为1 */
	if(limit>0xfffff)
	{
		access|=0x8000;
		limit/=0x1000;
	}
	GDT->base_high=(base>>24)&0xff;//取base高8位
	GDT->base_mid=(base>>16)&0xff;//取base中间8位
	GDT->base_low=base&0xffff;//取base低16位
	GDT->limit_high=((limit>>16)&0x0f)|((access>>8)&0xf0);
	GDT->limit_low=limit&0xffff;//取limit低16位
	GDT->access=access&0xff;//取access低8位
}
/* 设置IDT数据 */
void SetIDT(char count,int offset,short selector,char access)
{
	struct IDT_data *IDT=(struct IDT_data*)IDT_ADDR;
	IDT+=count;//设置IDT地址到地count个IDT处
	IDT->offset_high=(offset>>16)&0xffff;//取offset高16位
	IDT->offset_low=offset&0xffff;//取offset低16位
	IDT->selector=selector;
	IDT->count=0;
	IDT->access=access;
}