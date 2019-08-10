;----------------------------------------------
; initkfs, 2019
; Saves ONLY working registers, i.e. all registers except RDX, which is used to save errors
;----------------------------------------------
%macro push64wr 0

	push rax
	push rbx
	push rcx
	
	; push rdx
	
	push rbp
	push rdi
	push rsi
	
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15

%endmacro
