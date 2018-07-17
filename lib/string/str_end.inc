;----------------------------------------------
; initkfs, 2018
; procedure "str_end"
; Params: 1 - memory address of string, RDI. 2 - memory address of pattern, RSI
; Result: RAX, 1 if ends with pattern, or 0
; @TODO space char: 10, etc?
;----------------------------------------------
global str_end

str_end:
	.start:
	
	push rbx
	push rcx
	
	call str_length ; get string length
	cmp rax, 0 ; check correct length
	jle .patternNotFound
	
	mov rbx, rax ; save string length
	
	call str_search
	mov rcx, rax ; save finded index
	cmp rax, -1
	je .patternNotFound

	xchg rdi, rsi
	call str_length ; get pattern lenght
	cmp rax, 0
	jle .patternNotFound
	
	; rax - pattern length
	; rbx - string length
	; rcx - searched index
	; index + pattern length = string length
	add rcx, rax
	mov rdx, rcx
	
	cmp rbx, rcx
	je .patternFound
	
.patternNotFound:
	mov rax, 0
	jmp .end

.patternFound:
	mov rax, 1
	
.end:
	pop rcx
	pop rbx
	ret
;----------------------------------------------
;			procedure "str_end" end
;----------------------------------------------


