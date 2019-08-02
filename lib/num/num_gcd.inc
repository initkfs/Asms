; errno=1200
;----------------------------------------------
; initkfs, 2018
; procedure "num_gcd"
; Calculate "Greatest Common Devisor" based on Euclidean algorithm
; Params:
; RDI, first positive decimal number
; RSI, second positive decimal number
; Example:
;	;GCD(16, 40) = 8
;	mov rdi, 16
;	mov rsi, 40
;	call num_gcd ;8 in RAX
;
; Returns: RAX
; Error: if first number is not positive
; Error: if second number is not positive
;----------------------------------------------
global num_gcd

num_gcd:

	push rcx

	test rdi, rdi
	jle .errFirstNumberNotPositive
	
	test rsi, rsi
	jle .errSecondNumberNotPositive

	mov rax, rdi
    mov rcx, rsi

.leftGreater:
    cmp rax, rcx
    jl .rightGreater  
    jmp .while   
    
.rightGreater:
    xchg rax, rcx ; swap registers
    
; a (rax) = larger number, b (rcx) = smaller number
.while:
    xor rdx, rdx	; prevent error from div
    idiv rcx			; rax - result, rcx - remainder
    mov rax, rcx	; a = b
    mov rcx, rdx	; b = remainder
   
    test rcx, rcx	; while(b != 0)
    jne .while		; 
    
    xor rdx, rdx
    jmp .end
    
.errFirstNumberNotPositive:
	mov rdx, 1201
	jmp .end

.errSecondNumberNotPositive:
	mov rdx, 1202
 
.end:
	pop rcx
	ret
