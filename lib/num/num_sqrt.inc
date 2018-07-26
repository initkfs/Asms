;----------------------------------------------
; initkfs, 2018
; procedure "num_sqrt"
; RDI - source number
; Result in RAX
; TODO check negative
;----------------------------------------------
global num_sqrt

num_sqrt:

	push rdi
    fild qword [rsp]
    fsqrt
    fisttp qword [rsp]
    mov rax, [rsp]  
    pop rdi
 
.end:
	ret
;----------------------------------------------
;			procedure "num_sqrt" end
;----------------------------------------------
