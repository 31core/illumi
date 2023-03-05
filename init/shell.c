#include <version.h>
#include <kernel/fs/fs.h>
#include <kernel/task.h>
#include <kernel/user.h>
#include <kernel/memory.h>
#include <lib/string.h>
#include <lib/types.h>
#include <kernel/strfmt.h>
#include <device/video/cli_print.h>
#include <device/input/keyboard.h>

void shell(void)
{
	char user[20];
	user_get_name(user, task_get_uid(task_get_pid()));

	for(;;)
	{
		int i = 0;
		printfmt("[%s /] ", user);
		char inp[21],cmd[11];
		char dirname[20];
		input(inp);
		str_split(cmd, inp, " ", 0);
		/* 显示内核版本 */
		if(!str_cmp(cmd, "rever"))
		{
			printfmt("%s %s\n", KERNEL_NAME, KERNEL_VERSION);
		}
		/* 打印任务 */
		else if(!str_cmp(cmd, "ps"))
		{
			int pids[1024];
			int i = task_get_list(pids);
			int j = 0;
			cli_print("PID PPID UID Name\n");
			for(; j < i; j++)
			{
				char name[11];
				int ppid = task_get_ppid(pids[j]);
				int uid = task_get_uid(pids[j]);
				task_get_name(name, j);
				printfmt("%d   %d   %d   %s\n", pids[j], ppid, uid, name);
			}
		}
		/* 杀死任务 */
		else if(!str_cmp(cmd, "kill"))
		{
			char strpid[5];
			str_split(strpid, inp, " ", 1);
			int pid = str2uint(strpid);
			task_kill(pid);
		}
		/* 打印子目录及文件 */
		else if(!str_cmp(cmd, "ls"))
		{
			int inode_list[20];
			str_split(dirname, inp, " ", 1);
			int count = dir_list_inode(inode_list, dirname);
			for(i = 0; i < count; i++)
			{
				file_get_name_by_inode(dirname, inode_list[i]);
				printfmt("%s\n", dirname);
			}
		}
		/* 创建文件夹 */
		else if(!str_cmp(cmd, "mkdir"))
		{
			str_split(dirname, inp, " ", 1);
			dir_create(dirname);
		}
		/* 显示文件内容 */
		else if(!str_cmp(cmd, "cat"))
		{
			ST_FILE fp;
			char filename[10];
			char data[1024];
			str_cpy(data, "");
			str_split(filename, inp, " ", 1);
			if(file_open(&fp, filename) == -1)
			{
				printfmt("%s: no such file.\n", filename);
				continue;
			}
			int size = file_read(&fp, data, 0);
			for(i = 0; i < size; i++)
			{
				cli_print_char(data[i]);
			}
		}
		/* 删除文件 */
		else if(!str_cmp(cmd, "rm"))
		{
			char filename[10];
			str_split(filename, inp, " ", 1);
			file_remove(filename);
		}
		/* 打印内存使用情况 */
		else if(!str_cmp(cmd, "mem"))
		{
			unsigned int size = (unsigned int)mem_get_size() / 1024;
			printfmt("Total: %d KB\n", size);
			size = (unsigned int)mem_get_free_size() / 1024;
			printfmt("Free: %d KB\n", size);
		}
		else if(str_cmp(cmd, ""))
		{
			printfmt("%s: unkown command.\n", cmd);
		}
	}
}