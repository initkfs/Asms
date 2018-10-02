;----------------------------------------------
; initkfs, 2018
; procedure "str_start"
; Params: 
; RDI - memory address of string. 
; RSI - memory address of pattern.
; Return: RAX, 1 if starts with pattern, or 0
; Calls: str_search
;----------------------------------------------
global str_start

str_start:
	
	call str_search
	test rdx, rdx
	jne .end
	
	test rax, rax
	je .patternFound
	
.patternNotFound:
	xor rax, rax
	xor rdx, rdx
	jmp .end

.patternFound:
	mov rax, 1
	xor rdx, rdx
	
.end:
	ret
;----------------------------------------------
;			procedure "str_start" end
;----------------------------------------------


