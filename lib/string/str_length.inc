; errno=550
;----------------------------------------------
; initkfs, 2018
; procedure "str_length"
; Strings must end with a null character
; RDI: memory address of string with null character.
; Example:
; 	mov rdi, source ;source: db "Hello", 10, 0
;	call str_length ;RAX: 6
;	
; Returns: RAX - size of ASCII string with special characters except null character
; Error: if there is an overflow of the string length
;----------------------------------------------
global str_length

str_length:
	
	push rcx

	xor rcx, rcx
	
.length:
     mov al, byte [rdi + rcx]
     test al, al ; check is null-byte
     je .result
     
     inc rcx
     ;jc .errLengthOverflow
     jo .errLengthNumberOverflow
     jmp .length

.result:
	mov rax, rcx
	xor rdx, rdx
	jmp .end
	
.errLengthNumberOverflow:
	xor rax, rax
	mov rdx, 551

.end:
	pop rcx
	ret
