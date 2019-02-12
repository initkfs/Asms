; errno=1170
;----------------------------------------------
; initkfs, 2018
; procedure _array_element_offset
;
; Params: 
; RDI: array address
; RSI: array element index
;
; Returns: RAX, array memory address of the array element
;
; Calls: array_count, _array_size_specifier, _array_data_boundary_offset 
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
	mov rdx, 1171
	jmp .end
	
.end:
	pop r8
	pop rcx
	ret
