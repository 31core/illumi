#/init
OBJS=main.o

default:$(OBJS)
	echo /init

%.o:%.c
	gcc -m32 -I../include -c $*.c -o $*.o

clean:
	rm *.o