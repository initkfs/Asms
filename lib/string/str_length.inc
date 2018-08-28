; errno=550
;----------------------------------------------
; initkfs, 2018
; procedure "str_length"
; RDI: 1 - memory address of string.
;----------------------------------------------
global str_length

str_length:
	
	push rcx
	
	xor rax, rax
	xor rcx, rcx
	
.length:
     mov al, byte [rdi + rcx]
     cmp al, 0 ; null-byte
     je .result
     
     inc rcx
     jmp .length

.result:
	mov rax, rcx
	mov rdx, 0
	jmp .end

.end:
	pop rcx
	ret
