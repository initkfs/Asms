; errno=1150
;----------------------------------------------
; initkfs, 2018
; procedure "_array_size_specifier"
; Utility procedure for obtaining an array size specifier
; Params: 
; RDI, memory address of array
;
; Returns: RAX, array specifier size in bytes, positive number
; Error: if the value of the array specifier is not a positive number
; Note: Utility procedures should not be called in client code. For example, there may be no input validation and may contain unobvious behavior.
;----------------------------------------------
global _array_size_specifier

_array_size_specifier:

	movsx rax, byte [rdi]
	
	test rax, rax
	jle .arraySizeSpecifierIsZeroOrNegative
	
	xor rdx, rdx
	jmp .end
	
.arraySizeSpecifierIsZeroOrNegative:
	mov rdx, 1151

.end:
	ret
