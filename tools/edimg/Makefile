fs_objs = ../../kernel/fs/fs.o\
../../kernel/fs/init.o ../../kernel/fs/bitmap.o ../../kernel/fs/inode.o\
../../kernel/fs/block.o ../../kernel/fs/file.o ../../kernel/fs/dir.o ../../kernel/fs/path.o\
../../kernel/string.o

all:$(fs_objs) mem.o disk.o
	gcc -I../../include edimg.c $(fs_objs) mem.o disk.o -o edimg

%.o:%.c
	@echo "HOSTCC  $@"
	@gcc -Wall -I../../include -c $*.c -o $*.o

clean_deps:
	rm $(fs_objs)

clean:
	rm mem.o disk.o edimg
