#/init
OBJS=$(patsubst %.c,%.o,$(wildcard *.c))
C_FLAGS=-m32 -Wall -fno-stack-protector -I../include

default:$(OBJS)
	echo /init

%.o:%.c
	gcc $(C_FLAGS) -c $*.c -o $*.o

clean:
	rm *.o