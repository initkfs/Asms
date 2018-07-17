;----------------------------------------------
; initkfs, 2018
; procedure "str_start"
; Params: 1 - memory address of string, RDI. 2 - memory address of pattern, RSI
; Result: RAX, 1 if starts with pattern, or 0
;----------------------------------------------
global str_start

str_start:
	.start:
	
	call str_search
	cmp rax, 0
	je .patternFound
	
.patternNotFound:
	mov rax, 0
	jmp .end

.patternFound:
	mov rax, 1
	
.end:
	ret
;----------------------------------------------
;			procedure "str_start" end
;----------------------------------------------


