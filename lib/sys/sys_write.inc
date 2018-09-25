; errno=200
; initkfs, 2018
; 
; Print string to stdout
; RDI: string memory address, RSI: number of characters to print, or 0 for full string
; Calls: str_length
; ---------------------
global sys_write:

sys_write:

	push r8

	mov r8, rsi  ; save string size

	test r8, r8
	jl .errStringSizeNegative
	
	call str_length
	test rdx, rdx
	jne .end
	
	cmp r8, rax
	jg .errStringSizeGreater
	
	test r8, r8
	jg .print
	
	mov r8, rax
	
.print:
	mov rdx, r8 ; string size
	mov rax, 1 ; sys_write 
	mov rsi, rdi ; const char *buf
	mov rdi, 1 ; unsigned int fd; 1 - stdout
	
	syscall
	
	xor rdx, rdx
	jmp .end
	
.errStringSizeNegative:
	mov rdx, 201
	jmp .end

.errStringSizeGreater:
	mov rdx, 202

.end:
	pop r8
	ret
