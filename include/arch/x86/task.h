struct task_state
{
	int esp, ebp; //栈指针
	int eax, ebx, ecx, edx; //通用寄存器
	int esi, edi; //目标寄存器
};

void asm_task_switch(struct task_state*, struct task_state*);
void task_set_stack(struct task_state*, unsigned int);