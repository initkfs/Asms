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
	call bit_is_set
	test rdx, rdx
	je .fail
	
	dec rsi
	call bit_is_set
	test rdx, rdx
	je .fail
	
	mov rsi, 65
	call bit_is_set
	test rdx, rdx
	je .fail
	
	mov rdi, 1
	mov rsi, 1
	call bit_is_set
	test rdx, rdx
	jne .fail
	mov r8, 1
	cmp r8, rax
	jne .fail
	
	mov rdi, 256
	mov rsi, 9
	call bit_is_set
	test rdx, rdx
	jne .fail
	mov r8, 1
	cmp r8, rax
	jne .fail
	
	mov rdi, 1
	mov rsi, 2
	call bit_is_set
	test rdx, rdx
	jne .fail
	xor r8, r8
	cmp r8, rax
	jne .fail
	
	mov rdi, 128 ; 10000000
	mov rsi, 8
	call bit_is_set
	test rdx, rdx
	jne .fail
	mov r8, 1
	cmp r8, rax
	jne .fail
	
	mov rdi, 9223372036854775807
	mov rsi, 64
	call bit_is_set
	test rdx, rdx
	jne .fail
	mov r8, 0
	cmp r8, rax
	jne .fail

.end:
	call testSuccess
	
.fail:
	call assertNumeric
	mov rdi, __LINE__
	mov rsi, file
	call printFailInfo
