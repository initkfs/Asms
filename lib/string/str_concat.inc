;----------------------------------------------
; initkfs, 2018
; procedure "str_concat"
; Params: 1 - memory address of destination, RDI. 2 - memory address of string, RSI
;
;----------------------------------------------
global str_concat

str_concat:
	.start:
	
	push rcx
	
	mov rcx, 2
	call str_repeat
	
.end:
	pop rcx
	ret
;----------------------------------------------
;			procedure "str_concat" end
;----------------------------------------------


