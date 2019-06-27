; initkfs, 2018
; ---------------------

; include last
%include "tests/num/base_test_numeric.inc"

section .data
file: dq __FILE__

section .text
global main

main:

testNumCmp:

	;check long max negative equal
	mov rdi, -9223372036854775808
	mov rsi, rdi
	call num_cmpfd
	test rdx, rdx
	jne .fail
	
	xor r8, r8
	cmp r8, rax
	jne .fail
		
	;TODO adopt for large numbers
	;mov rdi, 9223372036854775807;
	;mov rsi, rdi
	;call num_cmpfd
	;test rdx, rdx
	;jne .fail
	
	xor r8, r8
	cmp r8, rax
	jne .fail

	mov rdi, __float64__(3.2)
	mov rsi, __float64__(3.2001)
	call num_cmpfd
	test rdx, rdx
	jne .fail
	
	mov r8, -1
	cmp r8, rax
	jne .fail
	
	mov rdi, __float64__(3.2001)
	mov rsi, __float64__(3.2)
	call num_cmpfd
	test rdx, rdx
	jne .fail
	
	mov r8, 1
	cmp r8, rax
	jne .fail
	
	call testSuccess
	
.fail:
	call assertNumeric
	mov rdi, __LINE__
	mov rsi, file
	call printFailInfo
