#/device/input
OBJS=$(patsubst %.c,%.o,$(wildcard *.c))

default:$(OBJS)
	echo /device/input

%.o:%.c
	gcc -m32 -Wall -I../../include -c $*.c -o $*.o
