;----------------------------------------------
; initkfs, 2018
; procedure "str_repeat"
; Params: 1 - memory address of destination, RDI. 2 - memory address of string, RSI, 3 - repeat count, RDX
;
;----------------------------------------------
global str_repeat

str_repeat:
	.start:
	
	xchg rdi, rsi
	call str_length
	xchg rdi, rsi
	
	mov rcx, rdx
.repeat:

	call str_copy
	lea rdi, [rdi + rax]
		
	loop .repeat

	mov [rdi], byte 0x00

.end:
	ret
;----------------------------------------------
;			procedure "str_repeat" end
;----------------------------------------------


