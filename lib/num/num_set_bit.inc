;----------------------------------------------
; initkfs, 2018
; procedure "num_set_bit"
; Params: 1 - unsigned number in RAX, 2 - n-bit in RDI
; Result in RAX
;
;y = x | (1 << n - 1)
;----------------------------------------------
global num_set_bit

num_set_bit:
	push rdi

	sub rdi, 1 ; n - 1
	
	xchg rdi, rax ; rax: n-bit, rdi: number
	call num1shl ; rax: 1 << n - 1
	
	xor rdi, rax
	mov rax, rdi ; set result
.end:
	pop rdi
	ret
;----------------------------------------------
;			procedure "num_set_bit" end
;----------------------------------------------
