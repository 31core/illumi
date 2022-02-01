#/arch/x86/boot
BINS = $(patsubst %.asm, %.bin, $(wildcard *.asm))

all:$(BINS);

%.bin:%.asm
	@echo "AS  arch/x86/boot/$@"
	@nasm $*.asm -o $*.bin

clean:
	rm *.bin