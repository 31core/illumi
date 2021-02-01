#/kernel
OBJS=string.o

default:$(OBJS)
	echo /kernel

%.o:%.c
	gcc -c -I../include $*.c -o $*.o

clean:
	rm *.o