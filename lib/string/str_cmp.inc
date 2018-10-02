;----------------------------------------------
; initkfs, 2018
; procedure "str_cmp"
; Params: 
; RDI - memory address of first string. 
; RSI - memory address second string, RSI
; Result: RAX - 1 if strings are equals. or 0
; Calls: str_length
;----------------------------------------------
global str_cmp

str_cmp:
	
	push rcx
	push rdi
	push rsi
	
	call str_length
	test rdx, rdx
	jne .end
	
	mov rcx, rax
	
	cld
	
	repe  cmpsb	
	jne .stringNotEquals ; do not use jecxz, last byte is lost
	
.stringEquals:
	mov rax, 1
	xor rdx, rdx
	jmp .end
	
.stringNotEquals:
	xor rax, rax
	xor rdx, rdx
	
.end:
	pop rsi
	pop rdi
	pop rcx
	ret
;----------------------------------------------
;			procedure "str_cmp" end
;----------------------------------------------


