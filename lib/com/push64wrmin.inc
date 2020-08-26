;----------------------------------------------
; initkfs, 2020
; Saves a minimal set of working registers, i.e. all registers except: 
; RDX which is used to save errors
; RAX which is used to return a value from procedure
;----------------------------------------------
%macro push64wrmin 0

	; push rax
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
