; initkfs, 2019
;----------------------------------------------
; Prints byte to stdout
; Params:
; RDI, contains byte character
;
; Example:
; 	mov dil, 'b'
; 	call sys_writeb  ; => b
;
; Calls: sys_write
; Note: Exit the procedure immediately if any non-system called function returns an error
; ---------------------
global sys_writeb:

sys_writeb:

	push rsi
	push rdi
	
	push rbp
	mov rbp, rsp
	sub rsp, 1
	and rsp, -16

	mov [rbp - 1], dil
	lea rdi, [rbp - 1]
	
	xor rsi, rsi
	inc rsi					; mov rsi, 1 ; number of characters to print

	call sys_write
	test rdx, rdx
	jne .end

	xor rdx, rdx

.end:
	mov rsp, rbp
	pop rbp
	
	pop rdi
	pop rsi
	ret
