; initkfs, 2018
; ---------------------

; include last
%include "tests/base_test.inc"
%include "lib/array/array.inc"

section .data
; don't move, use as array
array1element: dq 8
array2element: dq 6
array3element: dq 3
array4element: dq 9
array5element: dq 2
arrayElementsCount: dq 5

arraySizeSpecifier: dq 8

arraySorted: dq 2,3,6,8,9

section .bss
dataArray: resb 1 + 8 + 20;

section .text
global fillArray

fillArray:
	push rdi
	push rcx
	push rsi
	
	mov rdi, dataArray
	mov rsi, [arraySizeSpecifier]
	
	call array_init
	test rdx, rdx
	jne .error
	
	xor rcx, rcx
	
.addElement:

	mov rsi, rcx
	mov rdx, [array1element + rcx * 8]
	call array_set
	test rdx, rdx
	jne .error
	
	inc rcx
	
	cmp rcx, [arrayElementsCount]
	jl .addElement
	
	call array_count
	cmp rax, [arrayElementsCount]
	jne .error
	
	xor rdx, rdx
	jmp .end

.error:
	mov rdx, -1
	
.end:
	pop rsi
	pop rcx
	pop rdi
	ret

