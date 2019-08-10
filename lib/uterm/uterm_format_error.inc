;----------------------------------------------
; initkfs, 2019
; procedure "uterm_format_error"
; Prints white fonts on a red background.
; Calls: uterm_format
; Note: Exit the procedure immediately if any non-system called function returns an error
;----------------------------------------------
global uterm_format_error

uterm_format_error:

	; red on white: "[41m" 
	mov rdi, '41'
	call uterm_format
	test rdx, rdx
	jne .end
	
	xor rdx, rdx
	
.end:
	ret


