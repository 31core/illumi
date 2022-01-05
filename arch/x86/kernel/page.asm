global page_enable, set_cr3

;启用分页
page_enable:
    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax
    ret

set_cr3:
    mov eax, [esp + 4]
    mov cr3, eax
    ret