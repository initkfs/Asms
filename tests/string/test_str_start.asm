; initkfs, 2018
; ---------------------

%include "tests/string/base_test_string.inc"

section .data
file: dq __FILE__

section .text
global main

main:

testStringStart:

call testSuccess

	mov rdi, string1
	mov rsi, string1FirstLetter
	
	call str_start
	test rdx, rdx
	jne .fail
	
	mov r8, 1
	cmp rax, r8
	jne .fail
	
	mov rsi, string1NotContains
	call str_start
	test rdx, rdx
	jne .fail
	
	xor r8, r8
	cmp rax, r8
	jne .fail
	
	call testSuccess
	
.fail:
	call assertNumeric
	mov rdi, __LINE__
	mov rsi, file
	call printFailInfo
