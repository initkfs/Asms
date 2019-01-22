; initkfs, 2018
; ---------------------
%include "lib/array/array_utils.inc"
%include "lib/array/array_sort.inc"

; include last
%include "tests/array/base_test_array.inc"

section .data
file: dq __FILE__

section .text
global main

main:

testArraySort:

	call fillArray
	test rdx, rdx
	jne .fail
	
	mov rdi, dataArray
	call array_sort
	
	xor rcx, rcx
	
.compareElements:

	mov rsi, rcx
	call array_get
	test rdx, rdx
	jne .fail
	
	mov r8, [arraySorted + rcx * 8]
	cmp r8, rax
	jne .fail

	inc rcx
	cmp rcx, [arrayElementsCount]
	jl .compareElements
	
	call testSuccess
.fail:
	call assertNumeric
	mov rdi, __LINE__
	mov rsi, file
	call printFailInfo
