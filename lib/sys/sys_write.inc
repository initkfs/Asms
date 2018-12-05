; errno=200
; initkfs, 2018
; 
; Prints string to stdout
; RDI: memory address of string
; RSI: number of characters to print, or 0 for full string
; Calls: str_length
; System calls: sys_write
; Error: if string size in RSI is negative
; Error: if string size in RSI is larger than the string
; Error: if string length is zero, ex: string: db "", 0 will throw an error
; Error: sys_write system call error
; ---------------------
global sys_write:

sys_write:

	push r8
	push rax

	mov r8, rsi  ; save string size

	test r8, r8
	jl .errStringSizeNegative
	
	call str_length
	test rdx, rdx
	jne .end
	
	test rax, rax
	je .errStringSizeIsZero
	
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
	test rax, rax
	jl .syscallSysWriteError
	
	xor rdx, rdx
	jmp .end
	
.errStringSizeNegative:
	mov rdx, 201
	jmp .end

.errStringSizeGreater:
	mov rdx, 202
	jmp .end

.errStringSizeIsZero:
	mov rdx, 203
	jmp .end
	
.syscallSysWriteError:
	mov rdx, 204

.end:
	pop rax
	pop r8
	ret
