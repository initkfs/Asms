;----------------------------------------------
; initkfs, 2018
; procedure "dt_timestamp"
; Result in RAX
;----------------------------------------------
global dt_timestamp

dt_timestamp:

	push rdi

	mov     rax, 201         ; system call sys_time
    xor     rdi, rdi
    syscall 
    	
.end:
	pop rdi
	ret
;----------------------------------------------
;			procedure "dt_timestamp" end
;----------------------------------------------
