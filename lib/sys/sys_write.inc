; errno=200
; initkfs, 2018
; 
; Print string to stdout
; RDI: string memory address, RSI: number of characters to print, or 0 for full string
; ---------------------
global sys_write:

sys_write:

	push rdx

	mov rdx, rsi  ; save string size

	cmp rdx, 0
	jl .errStringSizeNegative
	
	call str_length
	cmp rax, 0
	jl .end
	
	cmp rdx, rax
	jg .errStringSizeGreater
	
	cmp rdx, 0
	jg .print
	
	mov rdx, rax
	
.print:

	mov rax, 1 ; sys_write 
	mov rsi, rdi ; const char *buf
	mov rdi, 1 ; unsigned int fd; 1 - stdout
	
	syscall
	jmp .end
	
.errStringSizeNegative:
	mov rax, -201
	jmp .end

.errStringSizeGreater:
	mov rax, -202
	jmp .end

.end:
	pop rdx
	mov rax, 0
	ret
