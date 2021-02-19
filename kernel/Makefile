#/kernel
OBJS=$(patsubst %.c,%.o,$(wildcard *.c))
C_FLAGS=-m32 -Wall -fno-stack-protector -I../include

default:$(OBJS);

%.o:%.c
	@echo [CC] kernel/$@
	@gcc $(C_FLAGS) -c $*.c -o $*.o