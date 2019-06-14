; errno=100
; initkfs, 2018
;  
; System exit
; RDI: exit code, positive number: 0 <= code <=255
;
; Example:
;	mov rdi, 2
;	call sys_exit
;
; System calls: sys_exit
; Error: if the return code is less than zero and more than 255
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
