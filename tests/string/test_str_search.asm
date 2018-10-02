; initkfs, 2018
; ---------------------

; include last
%include "tests/string/base_test_string.inc"

section .data
file: dq __FILE__

section .text
global main

main:

testStringSearch:

	mov rdi, string1
	mov rsi, string1SearchWord
	call str_search
	test rdx, rdx
	jne .fail
	
	cmp rax, [string1SearchWordIndex]
	jne .fail
	
	call testSuccess
	
.fail:
	mov rdi, __LINE__
	mov rsi, file
	call printFailInfo
