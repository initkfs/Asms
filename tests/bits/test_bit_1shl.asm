; initkfs, 2019
; ---------------------
%include "tests/bits/base_test_bits.inc"

section .data
file: dq __FILE__

section .text
global main

main:

testBits1Shl:

	mov rdi, -1
	call bit_1shl
	test rdx, rdx
	je .fail
	
	xor rdi, rdi
	call bit_1shl
	test rdx, rdx
	je .fail
	
	mov rdi, 256
	call bit_1shl
	test rdx, rdx
	je .fail
	
	mov rdi, 1
	call bit_1shl
	mov r8, 2 ; 1 << 1
	cmp r8, rax
	jne .fail
	
	mov rdi, 255
	call bit_1shl
	mov r8, 33554432 ; 1 << 255
	jne .fail

.end:
	call testSuccess
	
.fail:
	;call assertNumeric
	mov rdi, __LINE__
	mov rsi, file
	call printFailInfo
