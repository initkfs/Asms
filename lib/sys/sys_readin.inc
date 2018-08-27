; errno=300
; initkfs, 2018
; 
; RDI: char *buf, RSI: size_t count
; ---------------------
global sys_readin:

sys_readin:

	push rax
	push rdi
	push rsi
	
	cmp rsi, 0
	jle .errSizeIsZeroOrNegative

	;sys_read, rax: 0, rdi: unsigned int fd, rsi: char *buf , rdx: size_t count
	mov rdx, rsi ; buffer char size
	mov rsi, rdi ; char *buf
	mov rax, 0 ; sys_read
	mov rdi, 0 ; stdin
  
	syscall
	mov rdx, 0
	jmp .end
	
.errSizeIsZeroOrNegative:
	mov rdx, 301

.end:
	pop rsi
	pop rdi
	pop rax
	ret

