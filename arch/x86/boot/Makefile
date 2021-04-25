#/arch/x86/boot
BINS=$(patsubst %.asm,%.bin,$(wildcard *.asm))

all:$(BINS);

%.bin:%.asm
	@echo [NASM] arch/x86/kernel/$@
	@nasm $*.asm -o $*.bin

clean:
	rm *.bin