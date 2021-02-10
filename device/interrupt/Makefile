#/device/interrupt
OBJS=$(patsubst %.c,%.o,$(wildcard *.c))

default:$(OBJS)
	echo /device/interrupt

%.o:%.c
	gcc -m32 -I../../include -c $*.c -o $*.o
