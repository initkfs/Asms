; initkfs, 2019
;----------------------------------------------
; Prints a line break character '\r\n' without considering the operating system
;
; Calls: sys_writeb
; Note: Exit the procedure immediately if any non-system called function returns an error
; ---------------------
global sys_writeln:

sys_writeln:

	mov rdi, 13			; \r
	call sys_writeb
	test rdx, rdx
	jnz .end
	
	mov rdi, 10			; \n
	call sys_writeb
	test rdx, rdx
	jnz .end
	
	xor rdx, rdx

.end:
	ret
