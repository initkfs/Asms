;----------------------------------------------
; initkfs, 2018
; procedure "num_is_bit_set"
; Params: 1 - unsigned number in RAX, 2 - checked n-bit in RDI
; Result: in RAX: 1 - n-bit is set, 0 - n-bit not set
;
;1         00000001    (1<<0), n - 1 for starts numeration with 1
;1<<1      00000010
;
;if (x & (1<<n)) {
;  n-th bit is set
;}
;----------------------------------------------
global num_is_bit_set

num_is_bit_set:

	push rdi
	; rax - unsigned number, rdi - n-th bit
	sub rdi, 1 ; n - 1
	
	xchg rdi, rax ; swap rax and rdi, rax: n - 1, rdi: n-bit
	call num1shl ; rax: 1 << n - 1
	
	and rax, rdi
	jnz .bitSet

.bitNotSet:
	mov rax, 0
	jmp .end
	
.bitSet:
	mov rax, 1
	
.end:
	pop rdi
	ret
;----------------------------------------------
;			procedure "num_is_bit_set" end
;----------------------------------------------
