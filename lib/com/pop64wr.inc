;----------------------------------------------
; initkfs, 2019
; Restores ONLY working registers, i.e. all registers except RDX, which is used to save errors
;----------------------------------------------
%macro pop64wr 0

	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	
	pop rsi
	pop rdi
	pop rbp
	
	; pop rdx
	
	pop rcx
	pop rbx
	pop rax

%endmacro
