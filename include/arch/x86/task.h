struct task_state
{
	unsigned int esp, ebp; //栈指针
	unsigned int eax, ebx, ecx, edx; //通用寄存器
	unsigned int esi, edi; //目标寄存器
};

void task_set_stack(struct task_state*, void*);
