;----------------------------------------------
; initkfs, 2018
; procedure "num1shl" or  1 << n
; Params: 1 - n-bit in RAX (AL)
; Result in RAX
;----------------------------------------------
global num1shl

num1shl:
	push rcx

	mov cl, al ; required for shl
	mov rax, 1
	shl rax, cl ; 1 << n
	
	xor rdx, rdx
.end:
	pop rcx
	ret
	
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
	test rdx, rdx
	jne .end
	
	xor rdi, rax
	mov rax, rdi ; set result
	xor rdx, rdx
.end:
	pop rdi
	ret

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
	test rdx, rdx
	jne .end
	
	and rax, rdi
	jnz .bitSet

.bitNotSet:
	mov rax, 0
	xor rdx, rdx
	jmp .end
	
.bitSet:
	mov rax, 1
	xor rdx, rdx
	
.end:
	pop rdi
	ret

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
	test rdx, rdx
	jne .end
	
	not rax	
	and rax, rdi
	xor rdx, rdx
.end:
	pop rdi
	ret
