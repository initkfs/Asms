;----------------------------------------------
; initkfs, 2018
; procedure "num_gcd"
; Calculate Greatest Common Devisor based on Euclidean algorithm
; RDI - first number, RSI - second number
; Result in RAX
;----------------------------------------------
global num_gcd

num_gcd:

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
    div rcx			; rax - result, rcx - remainder
    mov rax, rcx	; a = b
    mov rcx, rdx	; b = remainder
   
    cmp rcx, 0		; while(b != 0)
    jne .while		; 
 
.end:
	ret
;----------------------------------------------
;			procedure "num_gcd" end
;----------------------------------------------
