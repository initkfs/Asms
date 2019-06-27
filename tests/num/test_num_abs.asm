; initkfs, 2018
; ---------------------

; include last
%include "tests/num/base_test_numeric.inc"

section .data
file: dq __FILE__
num1: dq 2147483648

section .text
global main

main:

testNumInt32Abs:

	mov rdi, 2147483648 ; int32 max + 1
	call num_int32_abs
	test rdx, rdx
	je .fail
	
	mov rdi, -2147483649 ; int32min + 1
	call num_int32_abs
	test rdx, rdx
	je .fail

	mov rdi, [num1]
	neg rdi
	call num_int32_abs
	test rdx, rdx
	jne .fail
	
	mov r8, [num1]
	cmp r8, rax
	jne .fail
	
	call testSuccess
	
.fail:
	call assertNumeric
	mov rdi, __LINE__
	mov rsi, file
	call printFailInfo
