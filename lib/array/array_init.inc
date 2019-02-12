; errno=1100
;----------------------------------------------
; initkfs, 2018
; procedure array_init
;
; Params: 
; RDI, memory address of array
; RSI, array size specifier in bytes, not negative, max 8
;----------------------------------------------
global array_init

array_init:

	test rsi, rsi
	jle .errInvalidArraySizeSpecifier
	
	cmp rsi, 8
	jg .errArraySizeSpicifierTooLarge
	
	; Array structure:
	;array_start_address|size_specifier_in_bytes (1 byte) |counter (8 bytes) |data...|array_end_address
	
	mov byte [rdi], sil ; set size
	lea rax, [rdi + 1] 
	mov qword [rax], 0 ; set array counter
	
	xor rdx, rdx
	jmp .end
	
.errInvalidArraySizeSpecifier:
	mov rdx, 1101
	jmp .end
	
.errArraySizeSpicifierTooLarge:
	mov rdx, 1102
	
.end:
	ret
