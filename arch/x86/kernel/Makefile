#/arch/x86/kernel
BINS=_start.bin
OBJS=graphics.o

default:$(BINS) $(OBJS)
	echo /arch/x86/kernel

%.bin:%.asm
	nasm $*.asm -f elf -o $*.bin

%.o:%.c
	gcc -c $*.c -o $*.o

clean:
	rm *.bin
	rm *.o