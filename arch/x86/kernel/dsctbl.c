#include<arch/x86/dsctbl.h>
#include<arch/x86/asmfunc.h>

void init_dsctbl()
{
	struct GDT_data *GDT=(struct GDT_data*)0x270000;
	struct IDT_data *IDT=(struct IDT_data*)0x26f800;
	int i;
	for(i=0;i<0x2000;i++)
	{
		SetGDT(GDT+i,0,0,0);
	}
	SetGDT(GDT+1,0,0xffffffff,0x4092);
	SetGDT(GDT+2,0x280000,0x7ffff,0x409a);
	LoadGDTR(0xffff,0x270000);//加载GDTR寄存器
	for(i=0;i<256;i++)
	{
		SetIDT(IDT+i,0,0,0);
	}
	LoadIDTR(0x7ff,0x26f800);//加载IDTR寄存器
}

void SetGDT(struct GDT_data* GDT,int base,int limit,int access)
{
	/* 大于1MB则置G为1 */
	if(limit>0xfffff)
	{
		access!=0x8000;
		limit/=0x1000;
	}
	GDT->base_high=(base>>24)&0xff;//取base高8位
	GDT->base_mid=(base>>16)&0xff;//取base中间8位
	GDT->base_low=base&0xffff;//取base低16位
	GDT->limit_high=((limit>>16)&0x0f)|((access>>8)&0xf0);
	GDT->limit_low=limit&0xffff;//取limit低16位
	GDT->access=access&0xff;//取access低8位
}

void SetIDT(struct IDT_data* IDT,int offset,int selector,int access)
{
	IDT->offset_high=(offset>>16)&0xffff;//取offset高16位
	IDT->offset_low=offset&0xffff;//取offset低16位
	IDT->selector=selector;
	IDT->count=(access>>8)&0xff;//取access高8位
	IDT->access=access&0xff;//取access低8位
}