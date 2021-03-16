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
	/* 初始化内存碎片管理 */
	init_MemFragCtl();
	AllocMemfragWithAddr(VGA_ADDR, 2 * 80 * 25); //显存
	AllocMemfragWithAddr(GDT_ADDR, 8 * 0x2000);
	AllocMemfragWithAddr(GDT_ADDR, 8 * 0x100);

	CleanupScreen();
	/* 操作系统主循环 */
	while(1)
	{
		print("[root /] ");
		char inp[21],cmd[11];
		input(inp);
		str_split(cmd, inp, ' ',0);
		/* 显示内核版本 */
		if(str_cmp(cmd, "rever") == 1)
		{
			print("Rexistum Kernel 0.0.2\n");
		}
		/* 打印任务 */
		else if(str_cmp(cmd, "ps") == 1)
		{
			int pids[1024];
			int i = ListTask(pids);
			int j = 0;
			print("PID Name\n");
			for(; j < i; j++)
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
		/* 杀死任务 */
		else if(str_cmp(cmd, "kill") == 1)
		{
			char strpid[5];
			str_split(strpid, inp, ' ',1);
			int pid=str2int(strpid);
			KillTask(pid);
		}
		/* 打印内存使用情况 */
		else if(str_cmp(cmd, "mem") == 1)
		{
			unsigned int size = GetMemorySize() / 1024;
			char str_size[11];
			print("Total: ");
			int2str(str_size, size);
			print(str_size);
			print(" KB\n");
			size = GetMemoryFreeSize() / 1024;
			int2str(str_size, size);
			print("Free: ");
			print(str_size);
			print(" KB\n");
		}
		else if(str_cmp(cmd, "") != 1)
		{
			char cmd[11];
			str_split(cmd, inp, ' ', 0);
			print(cmd);
			print(": unkown command.\n");
		}
	}
}