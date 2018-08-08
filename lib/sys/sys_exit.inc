;----------------------------------------------
; sys_exit
;  
; initkfs, 2018
; RDI: exis code
;----------------------------------------------
global sys_exit

sys_exit:

	mov rax, 60  ; sys_exit linux system call, linux 64 
	syscall
	
.end:
	ret
