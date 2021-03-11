#include <arch/x86/cpu.h>
#include <arch/x86/asmfunc.h>
#include <device/video/graphics.h>
#include <device/interrupt/init.h>
#include <device/input/keyboard.h>
#include <kernel/fifo.h>
#include <kernel/task.h>
#include <kernel/memory.h>
#include <kernel/string.h>
#include <kernel/types.h>

extern int timer_num, time_count;
extern struct fifo8 key_fifo;

int main()
{
	timer_num = 0;
	time_count = 0;
	init_fifo(&key_fifo, 0, 10);
	init_task(); //初始化多任务
	init_cpu(); //初始化cpu相关设定
	init_PIC(); //初始化PIC
	io_sti(); //启用中断
	init_MemFragCtl(); //初始化内存碎片管理

	CreateCurrentTask(); //创建当前任务
	SetTaskName(0, "init");

	CleanupScreen();
	/* 操作系统主循环 */
	while(1)
	{
		print("[root /] ");
		char inp[21];
		input(inp);
		/* 显示内核版本 */
		if(str_cmp(inp, "rever") == 1)
		{
			print("Rexistum Kernel 0.0.2\n");
		}
		/* 打印任务 */
		else if(str_cmp(inp, "ps") == 1)
		{
			int pids[1024];
			int i = ListTask(pids);
			int j = 0;
			print("PID Name\n");
			for(; j < i - 1; j++)
			{
				char str[11];
				int2str(str, pids[j]);
				print(str);
				print("  ");
				GetTaskName(str, j);
				print(str);
				printchar('\n');
			}
		}
		else if(str_cmp(inp, "") != 1)
		{
			char cmd[11];
			str_split(cmd, inp, ' ', 0);
			print(cmd);
			print(": unkown command.\n");
		}
	}
}