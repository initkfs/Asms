; errno=750
;----------------------------------------------
; initkfs, 2018
; procedure "num_sqrt"
; Params:
; RDI, positive number or zero
; Example:
;	mov rdi, 56169
;	call num_sqrt ; __float64__(237.0) in RAX
;
; Returns: RAX, result as a floating point number
; Calls: num_cmpfd
; Error: if input number is negative
; Note: Exit the procedure immediately if any non-system called function returns an error
;----------------------------------------------
global num_sqrt

num_sqrt:

	xor rsi, rsi
	call num_cmpfd
	test rdx, rdx
	jne .end
	
	cmp rax, -1
	je .errArgNumIsNegative
	
	test rax, rax
	je .returnZero

	push rdi
    fild qword [rsp]
    fsqrt
    fstp qword [rsp] ;or fist\fisttp for truncation result
    mov rax, [rsp]  
    pop rdi
    
    xor rdx, rdx
    jmp .end
    
.returnZero:
	xor rax, rax
	xor rdx, rdx
	jmp .end
   
.errArgNumIsNegative:
	mov rdx, 751
 
.end:
	ret
