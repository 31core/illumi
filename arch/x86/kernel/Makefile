#/arch/x86/kernel
BINS=$(patsubst %.asm,%.bin,$(wildcard *.asm))
OBJS=$(patsubst %.c,%.o,$(wildcard *.c))
C_FLAGS=-m32 -Wall -fno-stack-protector -I../../../include

default:$(BINS) $(OBJS);

%.bin:%.asm
	@echo [NASM] arch/x86/kernel/$@
	@nasm $*.asm -f elf -o $*.bin

%.o:%.c
	@echo [CC] arch/x86/kernel/$@
	@gcc $(C_FLAGS) -c $*.c -o $*.o