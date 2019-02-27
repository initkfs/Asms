;----------------------------------------------
; initkfs, 2018
; procedure "num_abs"
; Params:
; RDI - number
; Returns: RAX, absolute value of a number
;----------------------------------------------
global num_abs

num_abs:

	mov rax, rdi
	; rdi >>> 63, top bit isolation
	sar rax, 63
	
	; abs(x) = (x XOR y) - y
	mov rdx, rdi
	xor rdx, rax
	sub rdx, rax

	mov rax, rdx
	xor rdx, rdx
	
.end:
	ret
