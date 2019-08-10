;----------------------------------------------
; initkfs, 2019
; procedure "uterm_format_success"
; Prints white fonts on a green background.
; Calls: uterm_format
; Note: Exit the procedure immediately if any non-system called function returns an error
;----------------------------------------------
global uterm_format_success

uterm_format_success:

	; green on white: "[42m" 
	mov rdi, '42'
	call uterm_format
	test rdx, rdx
	jne .end
	
	xor rdx, rdx
	
.end:
	ret


