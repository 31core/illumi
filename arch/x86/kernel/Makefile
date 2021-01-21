#/arch/x86/kernel
BINS=_start.bin

default:$(BINS)
	echo /arch/x86/kernel

%.bin:%.asm
	nasm $*.asm -f elf -o $*.bin

clean:
	rm *.bin