; errno=1180
;----------------------------------------------
; initkfs, 2018
; procedure array_set
;
; Params: 
; RDI: array address, 
; RSI: array index, starts with 0
; RDX: new element
;
; Calls: array_count, _array_element_offset, _array_size_specifier, _array_counter_offset
;----------------------------------------------
global array_set

array_set:

	push rcx
	push rsi
	push r8
	push r9
	push r10
	push r11
	
	enter 8, 0
	
	mov [rbp - 8], rdx; save new array element
	mov r8, rdi ; save array address
	mov r9, rsi ; save array index
	
	test rsi, rsi
	jl .errArrayIndexLessZero
	
	call array_count
	test rax, rax
	je .addToEmptyArray
	
	cmp rsi, rax
	jg .errArrayIndexLargerArraySize
	jmp .startAdd
	
.addToEmptyArray:
	test rsi, rsi
	jne .errArrayIndexInvalidForEmptyArray

.startAdd:
	
	call _array_element_offset
	test rdx, rdx
	jne .end
	
	mov r10, rax ; R10: array element offset address, by index
	
	call _array_size_specifier
	test rdx, rdx
	jne .end
	
	mov r11, rax
	
	xor rcx, rcx
	
.moveByteToArray:
	lea rsi, [rbp - 8 + rcx] ; calculate address of byte from new element
	lea rdi, [r10 + rcx] ; calculate address of array
	movsb
	
	inc rcx
	cmp rcx, r11
	jne .moveByteToArray
	
.updateCounter:
	mov rdi, r8 ; restore array address
	call _array_counter_offset
	test rdx, rdx
	jne .end
	
	mov rcx, [rax]
	inc rcx
	mov [rax], rcx ; update counter
	
	xor rdx, rdx
	
	jmp .end
	
.errArrayIndexLessZero:
	mov rdx, 1181
	jmp .end

.errArrayIndexLargerArraySize:
	mov rdx, 1182
	jmp .end
	
.errArrayIndexInvalidForEmptyArray:
	mov rdx, 1183
	jmp .end
	
.end:
	leave
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rcx
	ret
