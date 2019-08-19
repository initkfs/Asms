;----------------------------------------------
; initkfs, 2019
; procedure "uterm_format_warning"
; Prints white fonts on a yellow background.
; Calls: uterm_format
; Note: Exit the procedure immediately if any non-system called function returns an error
;----------------------------------------------
global uterm_format_warning

uterm_format_warning:

	push rdi
	
	; red on white: "[43m" 
	mov rdi, '43'
	call uterm_format
	test rdx, rdx
	jne .end
	
	xor rdx, rdx
	
.end:
	pop rdi
	ret


