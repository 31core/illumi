struct task_status
{
	int esp;
	int eax,ebx,ecx,edx;
};

void RecordTaskStatus();
void RestoreTaskStatus();