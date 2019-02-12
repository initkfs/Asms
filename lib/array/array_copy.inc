;----------------------------------------------
; initkfs, 2018
; procedure "array_copy"
;
; Params: 
; RDI, array address
; RSI, array source index, starts with 0
; RDX, array destination index
;
; Calls: array_get, array_set
;----------------------------------------------
global array_copy

array_copy:

	push rsi
	push r9
	push r10
	
	mov r9, rdx ; save destination index

	call array_get
	test rdx, rdx
	jne .end
	
	mov r10, rax ; save source values
	
	mov rsi, r9
	mov rdx, r10
	call array_set
	test rdx, rdx
	jne .end
	
.end:
	pop r10
	pop r9
	pop rsi
	ret
