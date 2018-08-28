; initkfs, 2018
; ---------------------
%include "lib/array32/array_utils.inc"
%include "lib/array32/array_sort.inc"

; include last
%include "tests/array32/base_test_array.inc"

section .data
file: dq __FILE__

section .text
global main

main:

testArraySort:

	call fillArray
	cmp rdx, 0
	jne .fail
	
	mov rdi, dataArray
	call array_sort
	
	mov rcx, 0
.cmpElements:

	mov rsi, rcx
	call array_get
	cmp rdx, 0
	jne .fail
	
	mov r8b, [arraySorted + rcx]
	cmp r8b, al
	jne .fail


	inc rcx
	cmp rcx, [arrayElementsCount]
	jl .cmpElements
	
	call testSuccess
	
.fail:
	call assertNumeric
	mov rdi, __LINE__
	mov rsi, file
	call printFailInfo
