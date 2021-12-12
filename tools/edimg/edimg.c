#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <kernel/fs/fs.h>
#include <kernel/fs/init.h>
#include <kernel/fs/file.h>

#define IMAGE argv[1]
#define OPTION argv[2]
#define ARG1 argv[3]
#define ARG2 argv[4]

extern char image_file[50];

static int get_file_size(char *file)
{
	struct stat statbuf;
	stat(file, &statbuf);
	return statbuf.st_size;
}

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		printf("edimg tool version 0.1\n");
		printf("usage:\n");
		printf("edimg <image> <option> <args>...\n");
		printf("options:\n\
create\tCreate a file-system.\n\
write\tWrite a file into image.\n");
		exit(0);
	}

	strcpy(image_file, IMAGE);
	fs_init();

	ST_FILE file;
	FILE *fp;
	if(!strcmp(OPTION, "create"))
	{
		fs_create();
	}
	/* 写入文件 */
	else if(!strcmp(OPTION, "write"))
	{
		file_create(&file, ARG2);
		int size = get_file_size(ARG1);
		fp = fopen(ARG1, "r");
		char *data = malloc(size);
		for(int i = 0; i < size; i++)
		{
			data[i] = fgetc(fp);
		}
		file_write(&file, data, size);
		fclose(fp);
	}
	/* 读取文件 */
	else if(!strcmp(OPTION, "read"))
	{
		if(file_open(&file, ARG1) == FS_FAILED)
		{
			printf("edimg: unable to open '%s'.\n", ARG1);
			return -1;
		}
		fp = fopen(ARG2, "w");
		int size = file_get_size(file);
		char *data = malloc(size);
		file_read(&file, data, 0);
		for(int i = 0; i < size; i++)
		{
			fputc(data[i], fp);
		}
		fclose(fp);
	}
	else
	{
		printf("edimg: %s: unkown option.\n", OPTION);
	}
	return 0;
}