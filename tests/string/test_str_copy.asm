; initkfs, 2018
; ---------------------

; include last
%include "tests/string/base_test_string.inc"

section .data
file: dq __FILE__

section .bss
copyDest: resb 10

section .text
global main

main:

testStringCopy:

	mov rsi, string1
	mov rdi, copyDest
	call str_copy
	test rdx, rdx
	jne .fail
	
	xor rcx, rcx
.loop:
	
	mov al, byte [string1 + rcx]
	mov r8b, byte [copyDest + rcx]
	cmp al, r8b
	jne .fail
	
	inc rcx
	cmp rcx, [string1Size]
	jne .loop
	
	call testSuccess
	
.fail:
	mov rdi, __LINE__
	mov rsi, file
	call printFailInfo
