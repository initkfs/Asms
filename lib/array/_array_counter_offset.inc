;----------------------------------------------
; initkfs, 2018
; procedure "_array_counter_offset"
; Utility procedure for obtaining the address of an array counter
; Params: 
; RDI, memory address of array
;
; Returns: RAX, array counter memory offset
; Note: Utility procedures should not be called in client code. For example, there may be no input validation and may contain unobvious behavior.
;----------------------------------------------
global _array_counter_offset

_array_counter_offset:

	lea rax, [rdi + 1] ; add array size specifier in bytes: 1 byte
	xor rdx, rdx

.end:
	ret
