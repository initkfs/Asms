; ERROR_ID=40
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
	
	mov rax, 0
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
	jl .error
	
	jmp .end
.error: 
	mov rax, -1
	
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
	cmp rax, -1
	je .error
	
	mov eax, [rax]
	jmp .end
.error: 
	mov rax, -1
	
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
	push rdx
	
	cmp rsi, 0
	jl .error

	call array_size
	cmp rax, 0 ; if rax == -1 && size == 0
	jle .error
	
	cmp rsi, rax ; compare index and size
	jge .error ; index >= size
	
	mov rcx, rax

	call _array_data_boundary_offset
	cmp rax, -1
	je .error
	
	lea rax, [rax + rsi * 4] ; data offset + elements index * element size, where 4 for dword
	jmp .end

.error: 
	mov rax, -1
	
.end:
	pop rdx
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
	jl .error

	call _array_element_offset
	cmp rax, -1
	je .error
	
	mov eax, [rax]
	
	jmp .end
	
.error: 
	mov rax, -1
	
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
	push rdx
	push rsi

	cmp rsi, 0
	jl .error
	
	call array_size
	cmp rax, 0
	jl .error
	
	mov rcx, rax
	
	cmp rcx, 0
	je .writeToEmptyArray
	
	cmp rsi, rcx
	je .writeNewElement
	jg .error

	call _array_element_offset
	cmp rax, -1
	je .error
	
	mov [rax], edx
	jmp .updateCounter
	
.writeNewElement:

	mov rsi, rcx
	dec rsi
	call _array_element_offset ; get last value
	lea rax, [rax + 4]
	mov [rax], edx
	jmp .updateCounter
	
.writeToEmptyArray:
	call _array_data_boundary_offset
	mov [rax], edx

.updateCounter:
	call _array_size_offset
	mov ecx, [rax]
	inc ecx
	mov [rax], ecx ; update counter
	
	jmp .end
.error: 
	mov rax, -1
	
.end:
	pop rsi
	pop rdx
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
	push rdx

	call array_size
	cmp rax, -1
	je .error
	
	mov rdx, rsi
	mov rsi, rax

	call array_set
	cmp rax, -1
	je .error
	
	jmp .end
	
.error: 
	mov rax, -1
	
.end:
	pop rdx
	pop rdi
	pop rsi
	ret
