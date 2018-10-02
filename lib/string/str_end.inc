;----------------------------------------------
; initkfs, 2018
; procedure "str_end"
; Params: 
; RDI - memory address of string. 
; RSI - memory address of pattern, RSI
; Return: RAX, 1 if ends with pattern, or 0
; Calls: str_length, str_search
; @TODO space char: 10, etc?
;----------------------------------------------
global str_end

str_end:
	
	push r8
	push rcx
	
	call str_length
	test rdx, rdx
	jne .end
	
	test rax, rax ; check correct source string length
	jle .patternNotFound
	
	mov r8, rax ; save source string length
	
	call str_search
	test rdx, rdx
	jne .end
	
	mov rcx, rax ; save finded index
	cmp rax, -1
	je .patternNotFound

	xchg rdi, rsi
	call str_length ; get pattern lenght
	test rdx, rdx
	jne .end
	
	test rax, rax ; check correct pattern size
	jle .patternNotFound
	
	; rax - pattern length
	; r8 - string length
	; rcx - searched index
	; index + pattern length = string length
	add rcx, rax
	
	cmp r8, rcx
	je .patternFound
	
.patternNotFound:
	xor rax, rax
	xor rdx, rdx
	jmp .end

.patternFound:
	mov rax, 1
	xor rdx, rdx
	
.end:
	pop rcx
	pop rbx
	ret
;----------------------------------------------
;			procedure "str_end" end
;----------------------------------------------


