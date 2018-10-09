; errno=750
;----------------------------------------------
; initkfs, 2018
; procedure "num_sqrt"
; RDI - source number
; Result in RAX
; TODO check negative
;----------------------------------------------
global num_sqrt

num_sqrt:

	test rdi, rdi
	jl .errArgNumIsNegative

	push rdi
    fild qword [rsp]
    fsqrt
    fisttp qword [rsp]
    mov rax, [rsp]  
    pop rdi
    
    xor rdx, rdx
    jmp .end
   
.errArgNumIsNegative:
	mov rdx, 751
 
.end:
	ret
;----------------------------------------------
;			procedure "num_sqrt" end
;----------------------------------------------
