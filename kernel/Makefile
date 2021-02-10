#/kernel
OBJS=$(patsubst %.c,%.o,$(wildcard *.c))

default:$(OBJS)
	echo /kernel

%.o:%.c
	gcc -m32 -Wall -I../include -c $*.c -o $*.o

clean:
	rm *.o