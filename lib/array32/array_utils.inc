; errno=400
;----------------------------------------------
; array_init
;  
; initkfs, 2018
; RDI: array address
;----------------------------------------------
global array_init

array_init:
	
	; Array structure:
	; counter(dword)-data...

	mov dword [rdi], 0 ; set array counter
	
	mov rdx, 0
.end:
	ret
	
;----------------------------------------------
; _array_size_offset
;  
; initkfs, 2018
; RDI: array address
; Return RAX: 32bit array counter memory pointer
;----------------------------------------------
global _array_size_offset

_array_size_offset:

	lea rax, [rdi]; set counter
	cmp dword [rax], 0
	jl .errOffsetLessZero
	
	mov rdx, 0
	jmp .end

.errOffsetLessZero: 
	mov rdx, 401

.end:
	ret

;----------------------------------------------
; array_size
;  
; initkfs, 2018
; RDI: array address
; Return RAX: 32bit array size
;----------------------------------------------
global array_size

array_size:

	call _array_size_offset
	cmp rdx, 0
	jne .end
	
	mov eax, [rax]
	mov rdx, 0
	
.end:
	ret

;----------------------------------------------
; _array_data_boundary_offset
;  
; initkfs, 2018
; RDI: array address
; Return RAX: array memory address at which the array values begin
;----------------------------------------------
global _array_data_boundary_offset

_array_data_boundary_offset:

	lea rax, [rdi + 4] ; rdi + 4byte counter
	mov rdx, 0
.end:
	ret
	
;----------------------------------------------
; array_element_offset
;  
; initkfs, 2018
; RDI: array address, RSI: element index
; Return RAX: array memory address of the array element
;----------------------------------------------
global _array_element_offset

_array_element_offset:

	push rcx
	
	cmp rsi, 0
	jl .errArrayIndexLessZero

	call array_size
	cmp rdx, 0 ; if rax == -1 && size == 0
	jne .end
	
	cmp rax, 0
	jle .errArraySizeZeroOrLess
	
	cmp rsi, rax ; compare index and size
	jge .errArrayIndexGreaterThanSize ; index >= size
	
	mov rcx, rax

	call _array_data_boundary_offset
	cmp rdx, 0
	jne .end
	
	lea rax, [rax + rsi * 4] ; data offset + elements index * element size, where 4 for dword
	mov rdx, 0
	jmp .end
	
.errArrayIndexLessZero:
	mov rdx, 410
	jmp .end
	
.errArraySizeZeroOrLess:
	mov rdx, 411
	jmp .end
	
.errArrayIndexGreaterThanSize:
	mov rdx, 412
	jmp .end
	
.end:
	pop rcx
	ret
	
;----------------------------------------------
; array_get
;
; initkfs, 2018
; RDI: array address, RSI: array index, starts with 0
;----------------------------------------------
global array_get

array_get:

	cmp rsi, 0
	jl .arrayIndexLessZero

	call _array_element_offset
	cmp rdx, 0
	jne .end
	
	mov eax, [rax]
	mov rdx, 0
	jmp .end

.arrayIndexLessZero:
	mov rdx, 420
	
.end:
	ret
	
;----------------------------------------------
; array_set
;
; initkfs, 2018
; RDI: array address, RSI: array index, starts with 0, RDX: new element
;----------------------------------------------
global array_set

array_set:

	push rcx
	push rsi
	push r8
	
	mov r8, rdx ; save new element

	cmp rsi, 0
	jl .errArrayIndexLessZero
	
	call array_size
	cmp rdx, 0
	jne .end
	
	mov rcx, rax
	
	cmp rcx, 0
	je .writeToEmptyArray
	
	cmp rsi, rcx
	je .writeNewElement
	jg .errArrayIndexGreaterSizePerOne

	call _array_element_offset
	cmp rdx, 0
	jne .end
	
	mov [rax], r8d
	jmp .updateCounter
	
.writeNewElement:

	mov rsi, rcx
	dec rsi
	call _array_element_offset ; get last value
	cmp rdx, 0
	jne .end
	
	lea rax, [rax + 4]
	mov [rax], r8d
	jmp .updateCounter
	
.writeToEmptyArray:
	call _array_data_boundary_offset
	mov [rax], r8d

.updateCounter:
	call _array_size_offset
	cmp rdx, 0
	jne .end
	
	mov ecx, [rax]
	inc ecx
	mov [rax], ecx ; update counter
	
	mov rdx, 0
	jmp .end
	
.errArrayIndexLessZero:
	mov rdx, 430
	jmp .end

.errArrayIndexGreaterSizePerOne:
	mov rdx, 431
	jmp .end
	
.end:
	pop r8
	pop rsi
	pop rcx
	ret


;----------------------------------------------
; array_push
; 
; initkfs, 2018
; RDI: array address, RSI: element
;----------------------------------------------
global array_push

array_push:

	push rsi
	push rdi

	call array_size
	cmp rdx, 0
	jne .end
	
	mov rdx, rsi
	mov rsi, rax

	call array_set
	cmp rdx, 0
	jne .end
	
	mov rdx, 0
	
.end:
	pop rdi
	pop rsi
	ret
