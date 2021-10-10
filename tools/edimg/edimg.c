#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <kernel/fs/init.h>
#include <kernel/fs/file.h>

extern char image_file[50];

static int get_file_size(char *file)
{
	struct stat statbuf;
	stat(file, &statbuf);
	return statbuf.st_size;
}

int main(int argc, char *argv[])
{
	strcpy(image_file, argv[1]);
	fs_create();
	fs_init();

	ST_FILE file;
	FILE *fp;

	/* 写入文件 */
	if(strcmp(argv[2], "write") == 0)
	{
		file_create(&file, argv[4]);
		int size = get_file_size(argv[3]);
		fp = fopen(argv[3], "r");
		char *data = malloc(size);
		for(int i = 0; i < size; i++)
		{
			data[i] = fgetc(fp);
		}
		file_write(&file, data, size);
		fclose(fp);
	}
	return 0;
}