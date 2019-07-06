; errno=1250
;----------------------------------------------
; initkfs, 2018
; Procedure "bit_1shl". Equivalent to  1 << n
; Params: 
; RDI, The value that will be involved in the bit left shift 1 << n. The value must be greater than or equal to 1 and less than or equal to 64
; Example:
;	mov rdi, 19
;	call bit_1shl ; 524288 in RAX, or 1 << 19
;
; Returns: RAX, resulting value
; Error: if value out of bounds 1 <= value <= 64
;----------------------------------------------
global bit_1shl

bit_1shl:
	push rcx
	
	cmp rdi, 1
	jl .errValueLessThanOne
	
	cmp rdi, 64
	jg .errValueTooLarge

	mov cl, dil ; required for shl
	xor rax, rax
	inc rax ; mov rax, 1
	shl rax, cl ; 1 << n
	
	xor rdx, rdx
	jmp .end
	
.errValueLessThanOne:
	xor rax, rax
	mov rdx, 1251
	jmp .end
	
.errValueTooLarge:
	xor rax, rax
	mov rdx, 1252
	
.end:
	pop rcx
	ret
