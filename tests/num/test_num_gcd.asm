; initkfs, 2018
; ---------------------

; include last
%include "tests/num/base_test_numeric.inc"

section .data
file: dq __FILE__

section .text
global main

main:

testNumGCD:

	;GCD(16, 40) = 8
	mov rdi, 16
	mov rsi, 40
	call num_gcd
	test rdx, rdx
	jne .fail
	
	mov r8, 8
	cmp r8, rax
	jne .fail
	
	;GCD(344, 129) = 43
	mov rdi, 344
	mov rsi, 129
	call num_gcd
	test rdx, rdx
	jne .fail
	
	mov r8, 43
	cmp r8, rax
	jne .fail
	
	call testSuccess
	
.fail:
	call assertNumeric
	mov rdi, __LINE__
	mov rsi, file
	call printFailInfo
