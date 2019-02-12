;----------------------------------------------
; initkfs, 2018
; procedure _array_data_boundary_offset
;
; Params: 
; RDI, memory address of array
;
; Returns: RAX, array memory address at which the array values begin
;
; Calls: _array_counter_offset
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
