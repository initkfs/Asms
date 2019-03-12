; errno=600
;----------------------------------------------
; initkfs, 2018
; procedure "str_repeat"
; Params: 
; RDI, memory address of destination with the addition of null byte, 
; RSI, memory address of string, 
; RDX, repeat count, RDX
; Calls: str_length, str_copy
;----------------------------------------------
global str_repeat

str_repeat:

	push r8
	push rdi
	push rsi
	push rax
	
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
	pop rax
	pop rsi
	pop rdi
	pop r8
	ret
;----------------------------------------------
;			procedure "str_repeat" end
;----------------------------------------------


