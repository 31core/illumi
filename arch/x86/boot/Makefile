#/arch/x86/boot
BINS=$(patsubst %.asm,%.bin,$(wildcard *.asm))

default:$(BINS)
	echo /arch/x86/boot

%.bin:%.asm
	nasm $*.asm -o $*.bin

clean:
	rm *.bin