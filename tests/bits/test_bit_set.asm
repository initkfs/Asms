; initkfs, 2019
; ---------------------
%include "tests/bits/base_test_bits.inc"

section .data
file: dq __FILE__

section .text
global main

main:

testBitsSet:

	mov rdi, 1

	;test incorrect values in RSI
	xor rsi, rsi
	call bit_set
	test rdx, rdx
	je .fail
	
	dec rsi
	call bit_set
	test rdx, rdx
	je .fail
	
	mov rsi, 65
	call bit_set
	test rdx, rdx
	je .fail
	
	; test correct values
	mov rdi, 1
	mov rsi, 1
	call bit_set
	test rdx, rdx
	jne .fail
	mov r8, 1
	cmp r8, rax
	jne .fail
	
	mov rdi, 1
	mov rsi, 2
	call bit_set
	test rdx, rdx
	jne .fail
	mov r8, 3
	cmp r8, rax
	jne .fail
	
	mov rdi, 1 ;00000001
	mov rsi, 8
	call bit_set
	test rdx, rdx
	jne .fail
	mov r8, 129 ; 10000001
	cmp r8, rax
	jne .fail
	
	mov rdi, 9223372036854775807
	mov rsi, 64
	call bit_set
	test rdx, rdx
	jne .fail
	mov r8, 18446744073709551615
	cmp r8, rax
	jne .fail

.end:
	call testSuccess
.fail:
	call assertNumeric
	mov rdi, __LINE__
	mov rsi, file
	call printFailInfo
