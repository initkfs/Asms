;----------------------------------------------
; initkfs, 2018
; procedure "_array_data_boundary_offset"
; Utility procedure for obtaining the start of the data boundary in array
; Params: 
; RDI, memory address of array
;
; Returns: RAX, array memory address at which the array values begin
; Calls: _array_counter_offset
; Note: Utility procedures should not be called in client code. For example, there may be no input validation and may contain unobvious behavior.
; Note: Exit the procedure immediately if any non-system called function returns an error
;----------------------------------------------
global _array_data_boundary_offset

_array_data_boundary_offset:

	call _array_counter_offset
	test rdx, rdx
	jne .end
	
	lea rax, [rax + 8] ; array counter start address + array counter size (8 bytes)
	xor rdx, rdx
.end:
	ret
