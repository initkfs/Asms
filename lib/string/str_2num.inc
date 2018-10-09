;----------------------------------------------
; initkfs, 2018
; procedure "str_2num"
; Params: 
; RDI - memory address of string. 
; Return: RAX, number string representation
; Calls: extern atoi
; @TODO @FIXME save registers, add errors, etc
;----------------------------------------------
global str_2num:

extern atoi

str_2num:
	push rax
	push rcx
	push rsi
	push rdi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15

	call atoi
	//@TODO check error
	xor rdx, rdx

.end:
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rdi    
	pop rsi        
	pop rcx
	pop rax
	ret
