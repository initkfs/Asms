; errno=600
;----------------------------------------------
; initkfs, 2018
; procedure "str_repeat"
; Params: 
; Strings must end with a null character
; RDI, memory address of destination with the addition of null byte
; RSI, memory address of string
; RDX, repeat count
; Example:
;	mov rdi, dest
;	mov rsi, string
;	mov rdx, 2
;	call str_repeat
;
; Calls: str_length, str_copy
; Error: if count is negative
; Note: Exit the procedure immediately if any non-system called function returns an error
;----------------------------------------------
global str_repeat

str_repeat:

	push r8
	push rdi
	push rsi
	push rax
	push rcx
	
.start:

	test rdx, rdx
	jl .errCountIsNegative
	
	mov r8, rdx
	
	xchg rdi, rsi
	call str_length
	test rdx, rdx
	jne .end
	
	xchg rdi, rsi
	
	mov rcx, r8
	
.repeat:

	call str_copy
	test rdx, rdx
	jne .end
	
	lea rdi, [rdi + rax]
		
	loop .repeat

	mov [rdi], byte 0x00
	xor rdx, rdx
	jmp .end

.errCountIsNegative:
	mov rdx, 601

.end:
	pop rcx
	pop rax
	pop rsi
	pop rdi
	pop r8
	ret
;----------------------------------------------
;			procedure "str_repeat" end
;----------------------------------------------


