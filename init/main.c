#include<arch/x86/dsctbl.h>
#include<arch/x86/asmfunc.h>
#include<device/video/graphics.h>
#include<device/interrupt/init.h>
#include<device/input/keyboard.h>
#include<kernel/fifo.h>
#include<kernel/types.h>
#include<kernel/memory.h>
#include<kernel/string.h>

struct fifo8 key_fifo;
int main()
{
	init_fifo(&key_fifo,0,10);
	init_dsctbl();//初始化dsctbl
	init_pic();//初始化PIC
	io_sti();//启用中断
	init_MemFragCtl();//初始化内存碎片管理
	CleanupScreen();

	char *mem_size="          ";
	int2str(mem_size,GetMemorySize());
	print("Memory Total : ");
	print(mem_size);
	print(" Bytes\n");
	//操作系统主循环
	while(1)
	{
		print("[root /] ");
		char *inp="          ";
		input(inp);
		if(strcmp(inp,"rever")==1)
		{
			print("Rexistum Kernel 0.0.1\n");
		}
		else
		{
			print("command not found.\n");
		}
	}
}