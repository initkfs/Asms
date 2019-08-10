; errno=200
;----------------------------------------------
; initkfs, 2018
; Prints string to stdout
; RDI: memory address of string. Null-byte is ingnored
; RSI: number of characters to print. Be careful with utf.
;
; Example:
; 	mov rdi, source
;	mov rsi, 4
; 	call sys_write 
;
; System calls: sys_write
; Macros used: push64wr, pop64wr
; Error: if string size is not positive
; Error: if an error occurred while calling the syscall
;----------------------------------------------
global sys_write:

sys_write:

	push64wr
	
	test rsi, rsi
	jle .errStringSizeNotPositive
	
	;
	; preparing registers for syscall
	;
	
	mov rdx, rsi 	; string size
	
	xor rax, rax
	inc rax			; mov rax, 1 ; sys_write call number
		
	mov rsi, rdi 	; const char *buf, memory address of string
	
	xor rdi, rdi
	inc rdi			; mov rdi, 1 ; unsigned int fd; 1 - stdout
	
	syscall
	test rax, rax
	jl .syscallSysWriteError
	
	xor rdx, rdx
	jmp .end
	
.errStringSizeNotPositive:
	mov rdx, 201
	jmp .end
	
.syscallSysWriteError:
	mov rdx, 202

.end:
	pop64wr
	ret
