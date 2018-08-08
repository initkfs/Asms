; initkfs, 2018
; ---------------------
%include "lib/sys/sys_exit.inc"
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
	
	xor rax, rax
	call array_size
	cmp rax, 1
	jne .fail

	jmp testArrayGet
.fail:
	mov rdx, 1
	call assertNumeric
	mov rdi, __LINE__
	mov rsi, file
	call printFailInfo

testArrayGet:

	mov rdi, dataArray
	mov rsi, 0 ; index
	
	xor rax, rax
	call array_get
	
	cmp rax, [array1element]
	jne .fail

	jmp testSuccess
.fail:
	mov rdx, [array1element]
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
