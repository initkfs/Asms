;----------------------------------------------
; initkfs, 2018
; procedure "array_get"
; Get an element from array by index
; Params: 
; RDI: array address
; RSI: array index, starts with 0
; Returns: RAX, array element by index
; Example:
;	mov rdi, dataArrayAddress
;	mov rsi, 0 ; set element index
;	call array_get ; result in RAX
;
; Calls: _array_element_offset;
; Note: Exit the procedure immediately if any non-system called function returns an error
;----------------------------------------------
global array_get

array_get:
	
	call _array_element_offset
	test rdx, rdx
	jne .end
	
	mov rax, [rax]
	
	xor rdx, rdx
	
	jmp .end

.end:
	ret
