#include <arch/x86/cpu.h>
#include <arch/x86/asmfunc.h>
#include <device/video/graphics.h>
#include <device/interrupt/init.h>
#include <device/input/keyboard.h>
#include <kernel/fifo.h>
#include <kernel/task.h>
#include <kernel/ipc.h>
#include <kernel/memory.h>
#include <kernel/string.h>
#include <kernel/types.h>
#include <kernel/fs/init.h>
#include <kernel/fs/file.h>

extern int timer_num, time_count;
extern struct fifo8 key_fifo;

int main()
{
	timer_num = 0;
	time_count = 0;
	init_fifo(&key_fifo, 0, 10);
	task_init(); //初始化多任务
	pipe_init(); //初始化管道(pipe)
	cpu_init(); //初始化cpu相关设定
	PIC_init(); //初始化PIC
	io_sti(); //启用中断
	/* 初始化内存碎片管理 */
	memfrag_init();
	memfrag_alloc_with_addr(VGA_ADDR, 2 * 80 * 25); //显存
	memfrag_alloc_with_addr(GDT_ADDR, 8 * 0x2000);
	memfrag_alloc_with_addr(IDT_ADDR, 8 * 0x100);
	memfrag_alloc_with_addr(0x100000, 64 * 1024); //为内核分配64 kb空间
	fs_create();
	fs_init();
	video_cleanup();
	/* 操作系统主循环 */
	while(1)
	{
		int i = 0;
		print("[root /] ");
		char inp[21],cmd[11];
		input(inp);
		str_split(cmd, inp, " ", 0);
		/* 显示内核版本 */
		if(str_cmp(cmd, "rever") == 1)
		{
			print("Rexistum Kernel 0.0.2\n");
		}
		/* 打印任务 */
		else if(str_cmp(cmd, "ps") == 1)
		{
			int pids[1024];
			int i = task_get_list(pids);
			int j = 0;
			print("PID  PPID  Name\n");
			for(; j < i; j++)
			{
				char str[11];
				int2str(str, pids[j]);
				print(str);
				print("   ");
				int2str(str, task_get_parent_pid(pids[j]));
				print(str);
				print("    ");
				task_get_name(str, j);
				print(str);
				printchar('\n');
			}
		}
		/* 杀死任务 */
		else if(str_cmp(cmd, "kill") == 1)
		{
			char strpid[5];
			str_split(strpid, inp, " ",1);
			int pid=str2int(strpid);
			task_kill(pid);
		}
		/* 显示文件内容 */
		else if(str_cmp(cmd, "cat") == 1)
		{
			struct file fp;
			char filename[10];
			char data[1024];
			str_cpy(data, "");
			str_split(filename, inp, " ", 1);
			if(file_open(&fp, filename) == -1)
			{
				print(filename);
				print(": no such file.\n");
				continue;
			}
			int size = file_read(&fp, data, 0);
			for(i = 0; i < size; i++)
			{
				printchar(data[i]);
			}
		}
		/* 打印内存使用情况 */
		else if(str_cmp(cmd, "mem") == 1)
		{
			unsigned int size = mem_get_size() / 1024;
			char str_size[11];
			print("Total: ");
			int2str(str_size, size);
			print(str_size);
			print(" KB\n");
			size = mem_get_free_size() / 1024;
			int2str(str_size, size);
			print("Free: ");
			print(str_size);
			print(" KB\n");
		}
		else if(str_cmp(cmd, "") != 1)
		{
			//char cmd[11];
			//str_split(cmd, inp, " ", 0);
			print(cmd);
			print(": unkown command.\n");
		}
	}
}
