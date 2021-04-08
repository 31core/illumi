struct task_status
{
	int esp, ebp; //栈指针
	int eax, ebx, ecx, edx; //通用寄存器
	int esi, edi; //目标寄存器
};

void asm_task_switch(struct task_status*, struct task_status*);