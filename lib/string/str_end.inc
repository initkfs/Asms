; errno=950
;----------------------------------------------
; initkfs, 2018
; procedure "str_end"
; Params: 
; Strings must end with a null character
; RDI, memory address of string
; RSI, memory address of pattern
; Example:
;	mov rdi, str ;"Hello",0
;	mov rsi, pattern ;"o",0
;	call str_end
;
; Returns: RAX, 1 if string ends with pattern, or 0
; Calls: str_length, str_search
; Error: if there is an overflow of the string length
; Note: Exit the procedure immediately if any non-system called function returns an error
; @TODO space char: 10, etc?
;----------------------------------------------
global str_end

str_end:
	
	push rdi
	push rsi
	push r8
	push rcx
	
	call str_length
	test rdx, rdx
	jne .end
	
	test rax, rax ; check correct source string length
	jle .patternNotFound ; or error?
	
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
	jo .errStringLengthResultOverflow
	
	cmp r8, rcx
	je .patternFound
	
.patternNotFound:
	xor rax, rax
	xor rdx, rdx
	jmp .end

.patternFound:
	xor rax, rax
	inc rax		; mov rax, 1
	xor rdx, rdx
	jmp .end
	
.errStringLengthResultOverflow:
	xor rax, rax
	mov rdx, 951
	
.end:
	pop rcx
	pop r8
	pop rdi
	pop rsi
	ret
;----------------------------------------------
;			procedure "str_end" end
;----------------------------------------------


