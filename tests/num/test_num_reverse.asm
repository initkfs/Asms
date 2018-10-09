; initkfs, 2018
; ---------------------

; include last
%include "tests/num/base_test_numeric.inc"

section .data
file: dq __FILE__
num1: dq 134
num1Reverse: dq 431

section .text
global main

main:

testNumReverse:

	mov rdi, [num1]
	call num_reverse
	test rdx, rdx
	jne .fail
	
	cmp rax, [num1Reverse]
	jne .fail
	
	call testSuccess
	
.fail:
	mov rdi, __LINE__
	mov rsi, file
	call printFailInfo
