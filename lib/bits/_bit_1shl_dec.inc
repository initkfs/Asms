;----------------------------------------------
; initkfs, 2019
; Procedure "_bit_1shl_dec". Utility procedure equivalent to 1 << (n - 1)
; Params:
; RDI, The n-value that will be involved in the bit left shift 1 << (n - 1)
; Example:
;	mov rdi, 19
;	call _bit_1shl_dec ; RAX: 1 << (19 - 1)
;
; Returns: RAX, resulting value. If the result of the (n - 1) subtraction is zero, then 1 is returned
; Calls: bit_1shl
;
; Note: Exit the procedure immediately if any non-system called function returns an error
;
; Warning: Since the procedure is utility, the input data IS NOT VALIDATED. This is a client call task
;----------------------------------------------
global _bit_1shl_dec

_bit_1shl_dec:

	push r8
	push r9
	
	mov r8, rdi
	mov r9, r8
	dec r9
	test r9, r9
	je .setSourceAsOne
	
	mov rdi, r9
	call bit_1shl ; rax: 1 << n - 1
	mov rdi, r8 ; restore rdi
	jmp .end ; jump immediately, errors not checked
	
.setSourceAsOne:
	xor rdx, rdx
	xor rax, rax
	inc rax ; mov rax, 1
	
.end:
	pop r9
	pop r8
	ret
