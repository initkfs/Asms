; initkfs, 2018
; ---------------------

; include last
%include "tests/string/base_test_string.inc"

section .data
file: dq __FILE__

section .text
global main

main:

testStringEnd:

	mov rdi, string1
	mov rsi, string1EndWord
	call str_end
	test rdx, rdx
	jne .fail
	
	cmp rax, 1
	jne .fail
	
	call testSuccess
	
.fail:
	call assertNumeric
	mov rdi, __LINE__
	mov rsi, file
	call printFailInfo
