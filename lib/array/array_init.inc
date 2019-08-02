; errno=1100
;----------------------------------------------
; initkfs, 2018
; procedure "array_init"
; Initializes an array with the specified size of elements.
; Params: 
; RDI, memory address where the array starts
; RSI, array size specifier in bytes, not negative, maximum value: 8
; Example:
; 	mov rdi, dataArray
;	mov rsi, 4
;	call array_init ; each element is 4 bytes in size.
;
; Error: if the value of the array specifier is not a positive number
; Error: if the value of the array specifier is greater than 8
;----------------------------------------------
global array_init

array_init:

	test rsi, rsi
	jle .errInvalidArraySizeSpecifier
	
	cmp rsi, 8
	jg .errArraySizeSpicifierTooLarge
	
	; Array structure:
	; array_start_address | size_specifier_in_bytes (1 byte) | counter (8 bytes) | data... | array_end_address
	
	mov byte [rdi], sil 	; set element size
	lea rax, [rdi + 1] 		; calculate the address for the counter: add byte to the beginning of the array
	mov qword [rax], 0 		; set array counter
	
	xor rdx, rdx
	jmp .end
	
.errInvalidArraySizeSpecifier:
	mov rdx, 1101
	jmp .end
	
.errArraySizeSpicifierTooLarge:
	mov rdx, 1102
	
.end:
	ret
