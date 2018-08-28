; initkfs, 2018
; ---------------------

; include last
%include "tests/base_test.inc"

section .data
; don't move, use as array
array1element: dq 8
array2element: dq 6
array3element: dq 3
array4element: dq 9
array5element: dq 2
arrayElementsCount: dq 5

arraySorted: db 2,3,6,8,9

section .bss
dataArray: resb 4  + 20; 4byte counter +  5 * 4 bytes data

section .text

global fillArray
fillArray:
	push rdi
	push rcx
	push rax
	
	mov rdi, dataArray
	
	mov rcx, 0
	
.addElement:
	mov rsi, [array1element + rcx * 8]
	call array_push
	cmp rdx, 0
	jne .error
	
	inc rcx
	
	cmp rcx, [arrayElementsCount]
	jl .addElement
	
	call array_size
	cmp rax, [arrayElementsCount]
	jne .error
	
	mov rdx, 0
	jmp .end

.error:
	mov rdx, 1
	
.end:
	pop rax
	pop rcx
	pop rdi
	ret
