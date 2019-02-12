;----------------------------------------------
; initkfs, 2018
; procedure array_get
;
; Params: 
; RDI: array address, 
; RSI: array index, starts with 0
;
; Returns: RAX, array element by index
;
; Calls: _array_element_offset
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
