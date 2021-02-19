#存放源代码目录及子目录
asm_src=$(ARCH)/kernel/*.asm

c_src=init/*.c kernel/*.c\
device/video/*.c\
device/interrupt/*.c\
device/input/*.c\
$(ARCH)/kernel/*.c
