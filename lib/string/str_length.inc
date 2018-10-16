; errno=550
;----------------------------------------------
; initkfs, 2018
; procedure "str_length"
; RDI: 1 - memory address of string.
; Return: RAX: size of string
;----------------------------------------------
global str_length

str_length:
	
	push rcx
	
	xor rax, rax
	xor rcx, rcx
	
.length:
     mov al, byte [rdi + rcx]
     test al, al ; check is null-byte
     je .result
     
     inc rcx
     ;jc .errLengthOverflow
     jo .errLengthOverflow
     jmp .length

.result:
	mov rax, rcx
	xor rdx, rdx
	jmp .end
	
.errLengthOverflow:
	xor rax, rax
	mov rdx, 551

.end:
	pop rcx
	ret
