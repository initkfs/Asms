;----------------------------------------------
; initkfs, 2018
; procedure "str_length"
; Params: 1 - memory address of string, RDI.
;----------------------------------------------
global str_length

str_length:
	.start:
	
	push rcx
	
	enter 0, 0
	
	cmp rdi, 0
	je .notfound
	
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
	jmp .end
	
.notfound:
	mov rax, -1

.end:
	leave
	pop rcx
	ret
;----------------------------------------------
;			procedure "str_length" end
;----------------------------------------------
