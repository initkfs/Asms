; errno=1150
;----------------------------------------------
; initkfs, 2018
; procedure _array_size_specifier
;
; Params: 
; RDI, memory address of array
;
; Returns: RAX, array specifier size in bytes, positive number
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
