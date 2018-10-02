; initkfs, 2018
; ---------------------

; include last
%include "tests/string/base_test_string.inc"

section .data
file: dq __FILE__

section .text
global main

main:

testStringCompare:

	mov rdi, string1
	mov rsi, stringEqualsWithString1
	call str_cmp
	test rdx, rdx
	jne .fail
	
	cmp rax, 1
	jne .fail
	
	mov rsi, string2
	call str_cmp
	test rdx, rdx
	jne .fail
	
	cmp rax, 0
	jne .fail
	
	call testSuccess
	
.fail:
	mov rdi, __LINE__
	mov rsi, file
	call printFailInfo
