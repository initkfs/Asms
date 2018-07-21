;----------------------------------------------
; initkfs, 2018
; procedure "str_copy"
; Params: 1 - memory address of destination, RDI. 2 - memory address of string, RSI.
;
;----------------------------------------------
global str_copy

str_copy:
	.start:
	
	push rcx
	push rax
	push rdi
	push rsi
	
	xchg rdi, rsi
	call str_length ; get source length
	mov rcx, rax
	
	xchg rdi, rsi;

	cld
	rep movsb
	
	mov [rdi], byte 0x00 ; add null-byte
	
.end:
	pop rsi
	pop rdi
	pop rax
	pop rcx
	ret
;----------------------------------------------
;			procedure "str_copy" end
;----------------------------------------------


