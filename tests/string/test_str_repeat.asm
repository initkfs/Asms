; initkfs, 2018
; ---------------------

; include last
%include "tests/string/base_test_string.inc"

section .data
file: dq __FILE__

section .bss
strRepeated: resb 100

section .text
global main

main:

testStringRepeat:

	mov rdi, strRepeated
	mov rsi, string1
	mov rdx, 2
	
	call str_repeat
	test rdx, rdx
	jne .fail

	mov rdi, strRepeated
	call str_length
	test rdx, rdx
	jne .fail
	
	mov r8, [string1Size]
	add r8, [string1Size]
	
	cmp rax, r8
	jne .fail
	
	call testSuccess
	
.fail:
	mov rdx, r8
	mov rdi, __LINE__
	mov rsi, file
	call printFailInfo
