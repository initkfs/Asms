; errno=1160
;----------------------------------------------
; initkfs, 2018
; procedure "array_count"
; Params: 
; RDI, memory address of array
; Returns: RAX, array count, positive number
; Calls: _array_counter_offset
; Error: if array count is negative number
; Note: Exit the procedure immediately if any non-system called function returns an error
;----------------------------------------------
global array_count

array_count:

	call _array_counter_offset
	test rdx, rdx
	jne .end
	
	mov rax, [rax]
	
	test rax, rax
	jl .arrayCountIsNegative
	
	xor rdx, rdx
	jmp .end

.arrayCountIsNegative:
	mov rdx, 1161
.end:
	ret
