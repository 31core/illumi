#/device/interrupt
OBJS=$(patsubst %.c,%.o,$(wildcard *.c))

default:$(OBJS)
	echo /device/interrupt

%.o:%.c
	gcc -m32 -Wall -I../../include -c $*.c -o $*.o
