#/arch/x86/kernel
BINS=$(patsubst %.asm,%.bin,$(wildcard *.asm))
OBJS=$(patsubst %.c,%.o,$(wildcard *.c))
C_FLAGS=-m32 -Wall -fno-stack-protector -I../../../include

default:$(BINS) $(OBJS)
	echo /arch/x86/kernel

%.bin:%.asm
	nasm $*.asm -f elf -o $*.bin

%.o:%.c
	gcc $(C_FLAGS) -c $*.c -o $*.o
