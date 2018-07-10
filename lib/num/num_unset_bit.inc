;----------------------------------------------
; initkfs, 2018
; procedure "num_unset_bit"
; Params: 1 - unsigned number in RAX, 2 - n-bit in RDI
; Result in RAX
;
;y = x & ~(1<<n)
;----------------------------------------------
global num_unset_bit

num_unset_bit:
	push rdi
	sub rdi, 1 ; n - 1
	
	xchg rdi, rax ; rax: n-bit, rdi: number
	call num1shl ; rax: 1 << n - 1
	
	not rax	
	and rax, rdi
.end:
	pop rdi
	ret
;----------------------------------------------
;			procedure "num_unset_bit" end
;----------------------------------------------
