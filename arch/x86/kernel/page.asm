global page_enable, page_disable
global set_cr3

;启用分页
page_enable:
	mov eax, cr0
	or eax, 0x80000001
	mov cr0, eax
	ret

page_disable:
	mov eax, cr0
	and eax, 0x7fffffff
	mov cr0, eax
	ret

set_cr3:
	mov eax, [esp + 4]
	mov cr3, eax
	ret