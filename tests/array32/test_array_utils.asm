; initkfs, 2018
; ---------------------
%include "lib/array32/array_utils.inc"

; include last
%include "tests/array32/base_test_array.inc"

section .data
file: dq __FILE__

section .text
global main

main:

testArrayInit:
	
	mov rdi, dataArray
	
	call array_init
	cmp rax, 0
	jl .fail
	
	jmp testArrayEmptySize
	
.fail:
	mov rdi, __LINE__
	mov rsi, file
	call printFailInfo


testArrayEmptySize:

	mov rdi, dataArray
	call array_size
	
	cmp  rax, 0
	jne .fail

	jmp testArraySet
	
.fail:
	mov rdx, 0
	call assertNumeric
	mov rdi, __LINE__
	mov rsi, file
	call printFailInfo
	
testArraySet:

	mov rdi, dataArray
	mov rsi, 0 ; index
	mov rdx, [array1element]
	call array_set
	
	call array_get
	mov rdx, [array1element]
	cmp rax, [array1element]
	jne .fail
	
	mov rsi, 1
	mov rdx, [array2element]
	call array_set
	
	call array_get
	mov rdx, [array2element]
	cmp rax, [array2element]
	jne .fail

	jmp testArrayCorrectSize
.fail:
	call assertNumeric
	mov rdi, __LINE__
	mov rsi, file
	call printFailInfo

testArrayCorrectSize:

	mov rdi, dataArray
	
	call array_size
	cmp rax, 2
	jne .fail
	
	jmp testArrayPush
.fail:
	mov rdx, 2
	call assertNumeric
	mov rdi, __LINE__
	mov rsi, file
	call printFailInfo
	
	
testArrayPush:

	mov rdi, dataArray
	
	mov rsi, [array3element]
	call array_push
	mov rsi, [array4element]
	call array_push
	mov rsi, [array5element]
	call array_push
	
	mov rcx, 0
.iterate:

	mov rsi, rcx
	call array_get
	
	mov rdx, [array1element + rcx * 8]
	cmp rax, rdx
	jne .fail
	
	inc rcx
	cmp rcx, [arrayElementsCount]
	jl .iterate

	jmp testSuccess
.fail:
	call assertNumeric
	mov rdi, __LINE__
	mov rsi, file
	call printFailInfo

; ---------------------
; ---------------------
testFailed:
	mov rdi, -1
	call sys_exit

testSuccess:
	mov rdi, 0
	call sys_exit
