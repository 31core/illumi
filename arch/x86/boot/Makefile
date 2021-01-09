#/arch/x86/boot

BINS=boot.bin\
	loader.bin

default:$(BINS)
	echo /arch/x86/boot

%.bin:%.asm
	nasm $*.asm -o $*.bin

clean:
	rm *.bin