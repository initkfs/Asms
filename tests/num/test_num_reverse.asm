; initkfs, 2018
; ---------------------

; include last
%include "tests/num/base_test_numeric.inc"

section .data
file: dq __FILE__

section .text
global main

main:

testNumReverse:

	mov rdi, 134
	call num_reverse
	test rdx, rdx
	jne .fail
	
	mov r8, 431
	
	cmp r8, rax
	jne .fail
	
	call testSuccess
	
.fail:
	call assertNumeric
	mov rdi, __LINE__
	mov rsi, file
	call printFailInfo
