;----------------------------------------------
; initkfs, 2018
; procedure "str_concat"
; Params: 
; RDI memory address of destination. 
; RSI - memory address of string.
; Return: none
; Calls: str_repeat
;----------------------------------------------
global str_concat

str_concat:
	
	push rcx
	
	mov rcx, 2
	call str_repeat
	test rdx, rdx
	jne .end
	
	xor rdx, rdx
.end:
	pop rcx
	ret
;----------------------------------------------
;			procedure "str_concat" end
;----------------------------------------------


