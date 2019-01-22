; errno=1000
;----------------------------------------------
; array_init
;  
; initkfs, 2018
; RDI: array address
; RSI: size specifier in bytes, not negative, max 8
;----------------------------------------------
global array_init

array_init:

	test rsi, rsi
	jle .errInvalidArraySizeSpecifier
	
	cmp rsi, 8
	jg .errArraySizeSpicifierTooLarge
	
	; Array structure:
	;array_start_address|size_specifier_in_bytes (1 byte) |counter (8 bytes) |data...|array_end_address
	
	mov byte [rdi], sil ; set size
	lea rax, [rdi + 1] 
	mov qword [rax], 0 ; set array counter
	
	xor rdx, rdx
	jmp .end
	
.errInvalidArraySizeSpecifier:
	mov rdx, 1001
	jmp .end
	
.errArraySizeSpicifierTooLarge:
	mov rdx, 1002
	
.end:
	ret
	
	
;----------------------------------------------
; _array_size_specifier
;  
; initkfs, 2018
; RDI: array address
; Returns: RAX, array specifier size in bytes
;----------------------------------------------
global _array_size_specifier

_array_size_specifier:

	movsx rax, byte [rdi]
	xor rdx, rdx

.end:
	ret
	
	
;----------------------------------------------
; _array_counter_offset
;  
; initkfs, 2018
; RDI: array address
; Returns: RAX
;----------------------------------------------
global _array_counter_offset

_array_counter_offset:

	lea rax, [rdi + 1]
	xor rdx, rdx

.end:
	ret


;----------------------------------------------
; array_count
;  
; initkfs, 2018
; RDI: array address
; Returns: RAX, array counter
;----------------------------------------------
global array_count

array_count:

	call _array_counter_offset
	test rdx, rdx
	jne .end
	
	mov rax, [rax]
	
	xor rdx, rdx
.end:
	ret


;----------------------------------------------
; _array_data_boundary_offset
;  
; initkfs, 2018
; RDI: array address
; Returns: RAX, array memory address at which the array values begin
;----------------------------------------------
global _array_data_boundary_offset

_array_data_boundary_offset:

	call _array_counter_offset
	test rdx, rdx
	jne .end
	
	lea rax, [rax + 8]
	xor rdx, rdx
.end:
	ret
	
	
;----------------------------------------------
; _array_element_offset
;  
; initkfs, 2018
; RDI: array address
; RSI: element index
; Returns: RAX, array memory address of the array element
;----------------------------------------------
global _array_element_offset

_array_element_offset:

	push rcx
	push r8
	
	test rsi, rsi
	jl .errArrayIndexLessZero

	call array_count
	test rdx, rdx
	jl .end
	
	mov rcx, rax
	
	call _array_size_specifier
	test rdx, rdx
	jl .end
	
	mul rsi ; index * size
	; check jo
	mov r8, rax
	
	call _array_data_boundary_offset
	test rdx, rdx
	jne .end
	
	lea rax, [rax + r8] ; data offset + elements index * element size
	
	xor rdx, rdx
	jmp .end
	
.errArrayIndexLessZero:
	mov rdx, 410
	jmp .end
	
.end:
	pop r8
	pop rcx
	ret
	
;----------------------------------------------
; array_set
;
; initkfs, 2018
; RDI: array address, 
; RSI: array index, starts with 0
; RDX: new element
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
	mov rdx, 430
	jmp .end

.errArrayIndexLargerArraySize:
	mov rdx, 431
	jmp .end
	
.errArrayIndexInvalidForEmptyArray:
	mov rdx, 432
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
	

;----------------------------------------------
; array_get
;
; initkfs, 2018
; RDI: array address, 
; RSI: array index, starts with 0
; Returns: RAX, array element by index
;----------------------------------------------
global array_get

array_get:
	
	call _array_element_offset
	test rdx, rdx
	jne .end
	
	mov rax, [rax]
	
	xor rdx, rdx
	
	jmp .end

.end:
	ret
	
;----------------------------------------------
; array_copy
;
; initkfs, 2018
; RDI: array address, 
; RSI: array source index, starts with 0
; RDX: array destination index
;----------------------------------------------
global array_copy

array_copy:

	push rsi
	push r9
	push r10
	
	mov r9, rdx ; save destination index

	call array_get
	test rdx, rdx
	jne .end
	
	mov r10, rax ; save source values
	
	mov rsi, r9
	mov rdx, r10
	call array_set
	test rdx, rdx
	jne .end
	
.end:
	pop r10
	pop r9
	pop rsi
	ret
	
	
;----------------------------------------------
; array_remove
;
; initkfs, 2018
; RDI: array address, 
; RSI: array index, starts with 0
;----------------------------------------------
global array_remove

array_remove:

	push rsi
	push rcx
	push r9
	push r10

	call array_count
	test rdx, rdx
	jne .end
	
	mov rcx, rax
	dec rcx ; get last index
	
	cmp rsi, rcx
	je .updateCounter
	
	mov r9, rcx ; save last index
	mov rcx, rsi
	mov r10, rsi
	inc r10

.movArrayElement:

	mov rsi, r10
	mov rdx, rcx
	
	call array_copy
	test rdx, rdx
	jne .end
	
	cmp r10, r9
	je .updateCounter

	inc rcx
	inc r10
	
	jmp .movArrayElement

.updateCounter:	

	call _array_counter_offset
	test rdx, rdx
	jne .end
	
	mov rcx, [rax]
	dec rcx
	mov [rax], rcx
	
	xor rdx, rdx

.end:
	pop r10
	pop r9
	pop rcx
	pop rsi
	ret
	
	
	
	
