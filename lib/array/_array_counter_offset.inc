;----------------------------------------------
; initkfs, 2018
; procedure _array_counter_offset
;
; Params: 
; RDI, memory address of array
;
; Returns: RAX, array counter memory offset
;----------------------------------------------
global _array_counter_offset

_array_counter_offset:

	lea rax, [rdi + 1]
	xor rdx, rdx

.end:
	ret
