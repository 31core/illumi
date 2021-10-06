fs_objs = ../../kernel/fs/fs.o\
../../kernel/fs/init.o ../../kernel/fs/bitmap.o ../../kernel/fs/inode.o\
../../kernel/fs/block.o ../../kernel/fs/file.o ../../kernel/fs/dir.o ../../kernel/fs/path.o\
../../kernel/string.o

all:mem.o disk.o
	gcc -I../../include edimg.c $(fs_objs) mem.o disk.o -o edimg

mem.o:mem.c
	gcc -c mem.c -o mem.o

disk.o:disk.c
	gcc -c disk.c -o disk.o