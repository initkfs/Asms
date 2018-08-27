; errno=200
; initkfs, 2018
; 
; Print string to stdout
; RDI: string memory address, RSI: number of characters to print, or 0 for full string
; ---------------------
global sys_write:

sys_write:

	push r8

	mov r8, rsi  ; save string size

	cmp r8, 0
	jl .errStringSizeNegative
	
	call str_length
	cmp rdx, 0
	jne .end
	
	cmp r8, rax
	jg .errStringSizeGreater
	
	cmp r8, 0
	jg .print
	
	mov r8, rax
	
.print:
	mov rdx, r8 ; string size
	mov rax, 1 ; sys_write 
	mov rsi, rdi ; const char *buf
	mov rdi, 1 ; unsigned int fd; 1 - stdout
	
	syscall
	
	mov rdx, 0
	jmp .end
	
.errStringSizeNegative:
	mov rdx, 201
	jmp .end

.errStringSizeGreater:
	mov rdx, 202

.end:
	pop r8
	ret
