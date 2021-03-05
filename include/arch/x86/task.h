struct TSS
{
	int backlink,esp0,ss0,esp1,ss1,esp2,ss2,cr3;
	int eip,eflags,eax,ecx,edx,ebx,esp,ebp,esi,edi;//32位寄存器
	int es,cs,ss,ds,fs,gs;//16位寄存器
	int ldtr,iomap;
};