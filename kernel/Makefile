#/kernel
OBJS=string.o

default:$(OBJS)
	echo /kernel

%.o:%.c
	gcc -m32 -I../include -c $*.c -o $*.o

clean:
	rm *.o