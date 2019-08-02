; errno=1450
;----------------------------------------------
; initkfs, 2018
; procedure "array_copy"
; Params: 
; RDI, array address
; RSI, array source index, starts with 0
; RDX, array destination index
;
; Calls: array_get, array_set
; Error: if source index and destination index are equal
; Note: Exit the procedure immediately if any non-system called function returns an error
;----------------------------------------------
global array_copy

;TODO save registers
array_copy:

	cmp rsi, rdx
	je .errSourceIndexEqualDestIndex

	push rsi
	push r9
	push r10
	
	mov r9, rdx ; save destination index

	call array_get
	test rdx, rdx
	jne .end
	
	mov r10, rax ; save element
	
	mov rsi, r9
	mov rdx, r10
	call array_set
	test rdx, rdx
	jne .end
	
	xor rdx, rdx
	jmp .end

.errSourceIndexEqualDestIndex:
	mov rdx, 1451
	
.end:
	pop r10
	pop r9
	pop rsi
	ret
