; errno=1170
;----------------------------------------------
; initkfs, 2018
; procedure "_array_element_offset"
; Utility procedure for obtaining the start of the element offset with certain index
; Params: 
; RDI: array address
; RSI: array element index
;
; Returns: RAX, array memory address of the array element
; Calls: array_count, _array_size_specifier, _array_data_boundary_offset 
; Error: if array index less than 0
; Error: if an error occurred during the calculation of the element
; Note: Utility procedures should not be called in client code. For example, there may be no input validation and may contain unobvious behavior.
; Note: Exit the procedure immediately if any non-system called function returns an error
;----------------------------------------------
global _array_element_offset

_array_element_offset:

	push rcx
	push r8
	
	test rsi, rsi
	jl .errArrayIndexLessZero

	call array_count
	test rdx, rdx
	jne .end
	
	mov rcx, rax ; array size in rcx
	
	call _array_size_specifier
	test rdx, rdx
	jne .end
	
	imul rsi ; index * size
	jo .errArrayElementCalculateOverflow
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
	
.errArrayElementCalculateOverflow:
	mov rdx, 1172
	
.end:
	pop r8
	pop rcx
	ret
