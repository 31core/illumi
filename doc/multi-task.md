### 1.多任务简介
多任务是为不同的程序分配cpu时间片来实现多个程序同时运行.

### 2.多任务实现
在x86架构中有一个叫tr的任务寄存器,它回记录cpu的寄存器信息,从而在任务切换的时候恢复该任务状态.<br>
内核由计时器中断发生时进行任务切换(抢占式多任务).<br><br>

考虑到移植的方便,内核不采用tr寄存器,任务的寄存器信息将由内核代码保存.<br>
我们定义了一个```task_status```结构体来保存寄存器信息.
```
struct task_status
{
	int esp, ebp; //栈指针
	int eax, ebx, ecx, edx; //通用寄存器
	int esi, edi; //目标寄存器
};
```
asm_task_switch参数为2个```struct task_status```指针.
```
void asm_task_switch(struct task_status*, struct task_status*);
```
在asm_task_switch函数中实现了寄存器信息的保存.
```
	;保存当前任务状态
	mov eax,[esp+4]
	mov [eax],esp
	mov [eax+4],ebp
	mov [eax+8],eax
	mov [eax+12],ebx
	mov [eax+16],ecx
	mov [eax+20],edx
	mov [eax+24],esi
	mov [eax+28],edi
```
然后将下一个任务的寄存器信息恢复.
```
	;恢复下一个任务状态
	mov eax,[esp+8]
	mov esp,[eax]
	mov ebp,[eax+4]
	mov eax,[eax+8]
	mov ebx,[eax+12]
	mov ecx,[eax+16]
	mov edx,[eax+20]
	mov esi,[eax+24]
	mov edi,[eax+28]
	jmp [esp];返回时会返回到esp栈所指向的地址
```
最后的```jmp [esp]```会返回到该函数原本该返回的地址,此时esp栈的数据是下一个任务的数据,
中断函数结束后会执行```popad```指令弹出该任务中断前的数据,所以返回时会回到下一个任务中断的位置继续执行.<br>
ps.任务切换最重要的时esp栈的数据.