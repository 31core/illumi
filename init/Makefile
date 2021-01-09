#/init

OBJS=main.o

default:$(OBJS)
	echo /init

%.o:%.c
	gcc -c -I../include $*.c -o $*.o

clean:
	rm *.o