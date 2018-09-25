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
	
	test rsi, rsi
	jle .errSizeIsZeroOrNegative

	;sys_read: rax == 0, rdi: unsigned int fd, rsi: char *buf , rdx: size_t count
	mov rdx, rsi ; buffer char size
	mov rsi, rdi ; char *buf
	xor rax, rax ; rax == 0: sys_read
	xor rdi, rdi ; rdi == 0: stdin
  
	syscall
	xor rdx, rdx
	jmp .end
	
.errSizeIsZeroOrNegative:
	mov rdx, 301

.end:
	pop rsi
	pop rdi
	pop rax
	ret

