;----------------------------------------------
; initkfs, 2019
; procedure "uterm_format"
; Formats a string to display in the terminal
;
; Params:
; RDI, contains attribute combinations: '1;4' = 1 and 4 = bold and underlined
;
; Example:
; 	mov rdi, '1;4'
;	call uterm_format ; bold and underlined font
;
; Calls: sys_writeb, sys_writebs
; Note: Exit the procedure immediately if any non-system called function returns an error
;----------------------------------------------
global uterm_format

uterm_format:
	
	push rsi
	push rdi
	push r8
	
	push rbp
	mov rbp, rsp
	sub rsp, 8
	and rsp, -16
	
	mov r8, rdi 		; save attributes
	
	;\033[0m
	mov dil, 0x1b		; Escape character
	call sys_writeb
	test rdx, rdx
	jne .end
	
	mov dil, byte '['
	call sys_writeb
	test rdx, rdx
	jne .end
	
	mov rdi, r8
	xor rsi, rsi
	call sys_writebs
	test rdx, rdx
	jne .end
	
	mov dil, byte 'm'
	call sys_writeb
	test rdx, rdx
	jne .end
	
	xor rdx, rdx
	
.end:
	mov rsp, rbp
	pop rbp
	
	pop r8
	pop rdi
	pop rsi
	ret



