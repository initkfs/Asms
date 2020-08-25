;----------------------------------------------
; initkfs, 2018
; procedure "str_cmp"
; Params: 
; Strings must end with a null character
; RDI, memory address of first string
; RSI, memory address of second string
; Example:
;	mov rdi, string1
;	mov rsi, string2
;	call str_cmp
;
; Returns: RAX - 1 if strings are equals, or 0. Special characters are also compared
; Calls: str_length
; Note: Procedure sets comparison flags. Exit the procedure immediately if any non-system called function returns an error
;----------------------------------------------
global str_cmp

str_cmp:
	
	push rcx
	push rdi
	push rsi
	
	call str_length
	test rdx, rdx
	jne .end
	
	mov rcx, rax ;set count for repe
	
	cld
	
	repe cmpsb	
	jne .stringNotEquals ; do not use jecxz, last byte is lost
	
.stringEquals:
	xor rax, rax
	inc rax ; mov rax, 1
	xor rdx, rdx
	jmp .end
	
.stringNotEquals:
	xor rax, rax
	xor rdx, rdx
	
.end:

	cmp rax, 1

	pop rsi
	pop rdi
	pop rcx
	ret
;----------------------------------------------
;			procedure "str_cmp" end
;----------------------------------------------


