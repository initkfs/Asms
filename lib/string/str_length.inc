; errno=550
;----------------------------------------------
; initkfs, 2018
; procedure "str_length"
; RDI: memory address of string.
; Returns: RAX - size of ASCII string
;----------------------------------------------
global str_length

str_length:
	
	push rcx

	xor rcx, rcx
	
.length:
     mov al, byte [rdi + rcx]
     test al, al ; check is null-byte
     je .result
     
     inc rcx
     ;jc .errLengthOverflow
     jo .errLengthNumberOverflow
     jmp .length

.result:
	mov rax, rcx
	xor rdx, rdx
	jmp .end
	
.errLengthNumberOverflow:
	xor rax, rax
	mov rdx, 551

.end:
	pop rcx
	ret
