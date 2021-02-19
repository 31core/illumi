#/arch/x86/boot
BINS=$(patsubst %.asm,%.bin,$(wildcard *.asm))

default:$(BINS);

%.bin:%.asm
	@echo [NASM] $@
	@nasm $*.asm -o $*.bin

clean:
	rm *.bin