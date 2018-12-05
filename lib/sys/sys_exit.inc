; errno=100
; initkfs, 2018
;  
; System exit
; RDI: exit code, positive number: 0 <= code <=255
; System calls: sys_exit
;----------------------------------------------
global sys_exit

sys_exit:
	test rdi, rdi
	jl .errReturnCodeNegative
	
	cmp rdi, 255
	jg .errReturnCodeTooLarge
	
	jmp .exit

.errReturnCodeNegative:
	mov rdi, 101
	jmp .exit
	
.errReturnCodeTooLarge:
	mov rdi, 102

.exit:
	mov rdx, rdi
	mov rax, 60  ; sys_exit linux system call 
	syscall
	
.end:
	ret
