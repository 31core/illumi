#/arch/x86/kernel
BINS=$(patsubst %.asm,%.bin,$(wildcard *.asm))
OBJS=$(patsubst %.c,%.o,$(wildcard *.c))

default:$(BINS) $(OBJS)
	echo /arch/x86/kernel

%.bin:%.asm
	nasm $*.asm -f elf -o $*.bin

%.o:%.c
	gcc -m32 -Wall -I../../../include -c $*.c -o $*.o
