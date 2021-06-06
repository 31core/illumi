global cpuid_get_vendorid
global cpuid_get_brand
;获取cpu vendor ID
cpuid_get_vendorid:
	mov eax, 0
	cpuid
	mov eax, [esp + 4]
	mov [eax], ebx
	mov [eax + 4], edx
	mov [eax + 8], ecx
	mov byte [eax + 12], 0
	ret
;获取cpu商标信息
cpuid_get_brand:
	mov eax, 0x80000002
	cpuid
	mov esi, [esp + 4]
	mov [esi], eax
	mov [esi + 4], ebx
	mov [esi + 8], ecx
	mov [esi + 12], edx
	mov eax, 0x80000003
	cpuid
	mov esi, [esp + 4]
	mov [esi + 16], eax
	mov [esi + 20], ebx
	mov [esi + 24], ecx
	mov [esi + 28], edx
	mov eax, 0x80000004
	cpuid
	mov esi, [esp + 4]
	mov [esi + 32], eax
	mov [esi + 36], ebx
	mov [esi + 40], ecx
	mov [esi + 44], edx
	mov byte [esi + 48], 0
	ret