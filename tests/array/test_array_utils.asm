; initkfs, 2018
; ---------------------
%include "lib/array/array_utils.inc"

; include last
%include "tests/array/base_test_array.inc"

section .data
file: dq __FILE__

section .text
global main

main:

testArrayInit:
	
	mov rdi, dataArray
	mov rsi, [arraySizeSpecifier]
	
	call array_init
	test rdx, rdx
	jne .fail
	
	jmp testArraySizeSpecifier
	
.fail:
	mov rdi, __LINE__
	mov rsi, file
	call printFailInfo
	
	
testArraySizeSpecifier:
	
	mov rdi, dataArray
	call _array_size_specifier
	test rdx, rdx
	jne .fail
	
	mov rdx, rax 
	cmp rax, [arraySizeSpecifier]
	jne .fail
	
	jmp testArrayEmptyCount
.fail:
	mov r8, [arraySizeSpecifier]
	call assertNumeric
	mov rdi, __LINE__
	mov rsi, file
	call printFailInfo	
	
testArrayEmptyCount:
	
	mov rdi, dataArray
	call array_count
	test rdx, rdx
	jl .fail
	
	xor r8, r8
	cmp rax, r8
	jne .fail
	
	jmp testArraySet
.fail:
	call assertNumeric
	mov rdi, __LINE__
	mov rsi, file
	call printFailInfo	
	
	
testArraySet:

	mov rdi, dataArray
	mov rsi, 0
	mov rdx, [array1element]
	call array_set
	test rdx, rdx
	jl .fail
	
	mov r8, [array1element]
	
	call _array_data_boundary_offset
	mov rax, [rax]

	cmp r8, rax
	jne .fail
	
	
	mov rsi, 1
	mov rdx, [array2element]
	call array_set
	test rdx, rdx
	jl .fail
	
	mov r8, [array2element]
	
	call _array_element_offset
	mov rax, [rax]

	cmp r8, rax
	jne .fail
	
	jmp testArrayGet
.fail:
	call assertNumeric
	mov rdi, __LINE__
	mov rsi, file
	call printFailInfo	
	
testArrayGet:

	mov rdi, dataArray
	mov rsi, 0
	call array_get
	test rdx, rdx
	jne .fail
	
	mov r8, [array1element]
	jne .fail
	
	mov rsi, 1
	call array_get
	test rdx, rdx
	jne .fail
	
	mov r8, [array2element]
	cmp r8, rax
	jne .fail
	
	jmp testArrayRemoveLastElement
.fail:
	call assertNumeric
	mov rdi, __LINE__
	mov rsi, file
	call printFailInfo
	
testArrayRemoveLastElement:

	mov rdi, dataArray
	
	mov rsi, 2
	mov rdx, [array3element]
	call array_set
	test rdx, rdx
	jne .fail
	
	call array_remove
	test rdx, rdx
	jne .fail
	
	call array_count
	mov r8, 2
	cmp rax, r8
	jne .fail
	
	jmp testArrayRemoveElement
	
.fail:
	call assertNumeric
	mov rdi, __LINE__
	mov rsi, file
	call printFailInfo
	

testArrayRemoveElement:

	mov rdi, dataArray
	
	mov rsi, 2
	mov rdx, [array3element]
	call array_set
	test rdx, rdx
	jne .fail
	
	mov rsi, 1
	call array_remove
	test rdx, rdx
	jne .fail
	
	call array_get
	mov r8, [array3element]
	cmp rax, r8
	jne .fail
	
	call array_count
	mov r8, 2
	cmp rax, 2
	
	call testSuccess
.fail:
	call assertNumeric
	mov rdi, __LINE__
	mov rsi, file
	call printFailInfo
	



	
	



