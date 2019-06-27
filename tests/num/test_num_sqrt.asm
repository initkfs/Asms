; initkfs, 2018
; ---------------------

; include last
%include "tests/num/base_test_numeric.inc"

section .data
file: dq __FILE__

section .text
global main

main:

testNumSqrt:

	mov rdi, -1
	call num_sqrt
	test rdx, rdx
	je .fail
	
	mov rdi, 0
	call num_sqrt
	test rdx, rdx
	jne .fail
	
	xor r8, r8
	cmp r8, rax
	jne .fail
	
	mov rdi, 56169
	call num_sqrt
	test rdx, rdx
	jne .fail
	
	mov rdx, __float64__(237.0)
	movq xmm0, rdx
	movq xmm1, rax
	comisd xmm0, xmm1
	jnz .fail
	
	call testSuccess
	
.fail:
	mov rdi, __LINE__
	mov rsi, file
	call printFailInfo
