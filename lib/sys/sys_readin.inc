; errno=300
; initkfs, 2018
; 
; RDI: memory address of a buffer, 
; RSI: input string size (ASCII characters are implied)
;
; Example:
;	mov rdi, buff
;	mov rsi, 5
;	call sys_readin
;
; System calls: sys_read
; Error: if the string size is less than or equal to zero
; Error: if an error occurred while calling the sys_read
; Note: Exit the procedure immediately if any non-system called function returns an error
; ---------------------
global sys_readin:

sys_readin:

	push rax
	push rdi
	push rsi
	
	test rsi, rsi
	jle .errSizeIsZeroOrNegative

	;sys_read: rax == 0, rdi: unsigned int fd, rsi: char *buf , rdx: size_t count
	mov rdx, rsi ; buffer char size
	mov rsi, rdi ; char *buf
	xor rax, rax ; rax == 0: sys_read
	xor rdi, rdi ; rdi == 0: stdin
  
	syscall
	test rax, rax
	jl .errSysCallReadInError
	
	xor rdx, rdx
	jmp .end
	
.errSizeIsZeroOrNegative:
	mov rdx, 301
	jmp .end

.errSysCallReadInError:
	mov rdx, 302

.end:
	pop rsi
	pop rdi
	pop rax
	ret

