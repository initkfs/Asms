; initkfs, 2018
; ---------------------

; include last
%include "tests/num/base_test_numeric.inc"

section .data
file: dq __FILE__
num1: dq 134

section .text
global main

main:

testNumAbs:

	mov rdi, [num1]
	call num_abs
	test rdx, rdx
	jne .fail
	
	cmp rax, [num1]
	jne .fail
	
	mov r9, [num1]
	neg r9
	mov rdi, r9
	call num_abs
	test rdx, rdx
	jne .fail
	
	cmp rax, [num1]
	jne .fail
	
	call testSuccess
	
.fail:
	mov rdi, __LINE__
	mov rsi, file
	call printFailInfo
