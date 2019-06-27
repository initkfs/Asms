;----------------------------------------------
; initkfs, 2018
; procedure "str_copy"
; Params: 
; Strings must end with a null character
; RDI, memory address of destination with the addition of null byte
; RSI, memory address of string.
; Example:
;	mov rdi, copyDest
;	mov rsi, str
;	call str_copy
;
; Calls: str_length
; Note: Exit the procedure immediately if any non-system called function returns an error
;----------------------------------------------
global str_copy

str_copy:
	
	push rcx
	push rax
	push rdi
	push rsi
	
	xchg rdi, rsi
	call str_length ; get source length
	test rdx, rdx
	jne .end
	
	mov rcx, rax
	
	xchg rdi, rsi;

	cld
	rep movsb ; copy from rdi to rsi
	
	mov [rdi], byte 0x00 ; add null-byte
	
	xor rdx, rdx
.end:
	pop rsi
	pop rdi
	pop rax
	pop rcx
	ret
;----------------------------------------------
;			procedure "str_copy" end
;----------------------------------------------


