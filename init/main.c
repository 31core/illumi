#include <kernel/init.h>
#include <kernel/types.h>
#include <kernel/string.h>
#include <kernel/string_format.h>
#include <kernel/fs/init.h>
#include <kernel/fs/file.h>
#include <kernel/fs/dir.h>
#include <kernel/task.h>
#include <kernel/memory.h>
#include <device/video/graphics.h>
#include <device/input/keyboard.h>

int main()
{
	kernel_init(); //初始化内核
	fs_create();
	fs_init();
	video_cleanup();
	/* 操作系统主循环 */
	while(1)
	{
		int i = 0;
		print("[root /] ");
		char inp[21],cmd[11];
		char dirname[20];
		input(inp);
		str_split(cmd, inp, " ", 0);
		/* 显示内核版本 */
		if(str_cmp(cmd, "rever") == 1)
		{
			print("Rexistum Kernel 0.0.3\n");
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
				char name[11];
				int ppid = task_get_parent_pid(pids[j]);
				task_get_name(name, j);
				print_format("%d      %d    %s\n", pids[i], ppid, name);
			}
		}
		/* 杀死任务 */
		else if(str_cmp(cmd, "kill") == 1)
		{
			char strpid[5];
			str_split(strpid, inp, " ", 1);
			int pid = str2uint(strpid);
			task_kill(pid);
		}
		/* 打印子目录及文件 */
		else if(str_cmp(cmd, "ls") == 1)
		{
			int inode_list[20];
			str_split(dirname, inp, " ", 1);
			int count = dir_list_inode(inode_list, dirname);
			for(i = 0; i < count; i++)
			{
				file_get_name_by_inode(dirname, inode_list[i]);
				print_format("%s\n", dirname);
			}
		}
		/* 创建文件夹 */
		else if(str_cmp(cmd, "mkdir") == 1)
		{
			str_split(dirname, inp, " ", 1);
			dir_create(dirname);
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
				print_format("%s: no such file.\n", filename);
				continue;
			}
			int size = file_read(&fp, data, 0);
			for(i = 0; i < size; i++)
			{
				printchar(data[i]);
			}
		}
		/* 删除文件 */
		else if(str_cmp(cmd, "rm") == 1)
		{
			char filename[10];
			str_split(filename, inp, " ", 1);
			file_remove(filename);
		}
		/* 打印内存使用情况 */
		else if(str_cmp(cmd, "mem") == 1)
		{
			unsigned int size = mem_get_size() / 1024;
			print_format("Total: %d KB\n", size);
			size = mem_get_free_size() / 1024;
			print_format("Free: %d KB\n", size);
		}
		else if(str_cmp(cmd, "") != 1)
		{
			print_format("%s: unkown command.\n", cmd);
		}
	}
}
