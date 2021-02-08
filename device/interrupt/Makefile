#/device/pic
OBJS=$(patsubst %.c,%.o,$(wildcard *.c))

default:$(OBJS)
	echo /device/pic

%.o:%.c
	gcc -m32 -I../../include -c $*.c -o $*.o
