; initkfs, 2019
; ---------------------
%include "tests/bits/base_test_bits.inc"

section .data
file: dq __FILE__

section .text
global main

main:

testBitsIsSet:

	mov rdi, 1
	
	;test incorrect values in RSI
	xor rsi, rsi
	call bit_unset
	test rdx, rdx
	je .fail
	
	dec rsi
	call bit_unset
	test rdx, rdx
	je .fail
	
	mov rsi, 65
	call bit_unset
	test rdx, rdx
	je .fail
	
	mov rdi, 1
	mov rsi, 1
	call bit_unset
	test rdx, rdx
	jne .fail
	xor r8, r8
	cmp r8, rax
	jne .fail
	
	mov rdi, 192 ;11000000
	mov rsi, 7 
	call bit_unset
	test rdx, rdx
	jne .fail
	mov r8, 128 ;10000000
	cmp r8, rax
	jne .fail
	
	mov rdi, 18446744073709551615
	mov rsi, 64
	call bit_unset
	test rdx, rdx
	jne .fail
	mov r8, 9223372036854775807
	cmp r8, rax
	jne .fail
	
.end:
	call testSuccess
	
.fail:
	call assertNumeric
	mov rdi, __LINE__
	mov rsi, file
	call printFailInfo
