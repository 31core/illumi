#include<arch/x86/cpu.h>
#include<arch/x86/asmfunc.h>
#include<device/video/graphics.h>
#include<device/interrupt/init.h>
#include<device/input/keyboard.h>
#include<kernel/fifo.h>
#include<kernel/memory.h>
#include<kernel/string.h>
int timer_num;
struct fifo8 key_fifo;
int main()
{
	timer_num=0;
	init_fifo(&key_fifo,0,10);
	init_cpu();//初始化cpu相关设定
	init_PIC();//初始化PIC
	io_sti();//启用中断
	init_MemFragCtl();//初始化内存碎片管理
	CleanupScreen();
	//操作系统主循环
	while(1)
	{
		print("[root /] ");
		char inp[21];
		input(inp);
		if(str_cmp(inp,"rever")==1)
		{
			print("Rexistum Kernel 0.0.1\n");
		}
		else if(str_cmp(inp,"")!=1)
		{
			char cmd[11];
			str_split(cmd,inp,' ',0);
			print(cmd);
			print(": unkown command.\n");
		}
	}
}