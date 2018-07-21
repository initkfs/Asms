;----------------------------------------------
; initkfs, 2018
; procedure "str_cmp"
; Params: 1 - memory address of first string, RDI. 2 - memory address second string, RSI
; Result: RAX - 1 if strings are equals. or 0
;----------------------------------------------
global str_search

str_cmp:
	.start:
	
	push rcx
	
	call str_length
	mov rcx, rax
	
	cld
	
	repe  cmpsb	
	jne .stringNotEquals ; do not use jecxz, last byte is lost
	
.stringEquals:
	mov rax, 1
	jmp .end
	
.stringNotEquals:
	mov rax, 0
	
.end:
	pop rcx
	ret
;----------------------------------------------
;			procedure "str_cmp" end
;----------------------------------------------


