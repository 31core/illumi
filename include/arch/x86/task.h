struct task_status
{
	int esp;
	int eax,ebx,ecx,edx;
};

void asm_SwitchTask(struct task_status*,struct task_status*);