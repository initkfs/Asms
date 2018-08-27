; errno=100
; initkfs, 2018
;  
; System exit
; RDI: positive number, exit code
;----------------------------------------------
global sys_exit

sys_exit:
	cmp rdi, 0
	jl .errReturnCodeNegative
	
	cmp rdi, 255
	jg .errReturnCodeTooLarge
	
	jmp .exit

.errReturnCodeNegative:
	mov rdi, 101 ; error code, 0 <= code <=255
	jmp .exit
	
.errReturnCodeTooLarge:
	mov rdi, 102

.exit:
	mov rdx, rdi
	mov rax, 60  ; sys_exit linux system call 
	syscall
	
.end:
	ret
