;----------------------------------------------
; initkfs, 2018
; procedure "str_start"
; Params: 
; Strings must end with a null character
; RDI, memory address of string. 
; RSI, memory address of pattern.
; Example:
;	mov rdi, str ;"Hello",0
;	mov rsi, pattern ;"H",0
;	call str_start
;
; Returns: RAX, 1 if string starts with pattern, or 0
; Calls: str_search
; Note: Exit the procedure immediately if any non-system called function returns an error
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
	xor rax, rax
	inc rax ; mov rax, 1
	xor rdx, rdx
	
.end:
	ret
;----------------------------------------------
;			procedure "str_start" end
;----------------------------------------------


