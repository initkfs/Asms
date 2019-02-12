;----------------------------------------------
; initkfs, 2018
; procedure array_remove
;
; Params: 
; RDI: array address, 
; RSI: array index, starts with 0
;
; Returns: RAX, array element by index
;
; Calls: array_count, array_copy, _array_counter_offset
;----------------------------------------------
global array_remove

array_remove:

	push rsi
	push rcx
	push r9
	push r10

	call array_count
	test rdx, rdx
	jne .end
	
	mov rcx, rax
	dec rcx ; get last index
	
	cmp rsi, rcx
	je .updateCounter
	
	mov r9, rcx ; save last index
	mov rcx, rsi
	mov r10, rsi
	inc r10

.movArrayElement:

	mov rsi, r10
	mov rdx, rcx
	
	call array_copy
	test rdx, rdx
	jne .end
	
	cmp r10, r9
	je .updateCounter

	inc rcx
	inc r10
	
	jmp .movArrayElement

.updateCounter:	

	call _array_counter_offset
	test rdx, rdx
	jne .end
	
	mov rcx, [rax]
	dec rcx
	mov [rax], rcx
	
	xor rdx, rdx

.end:
	pop r10
	pop r9
	pop rcx
	pop rsi
	ret
	
	
	
	
