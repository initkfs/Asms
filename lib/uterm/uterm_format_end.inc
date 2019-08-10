;----------------------------------------------
; initkfs, 2019
; procedure "uterm_format_end"
; Restore default formatting settings. This is equivalent to printing a special sequence \e[0m
; Calls: uterm_format
; Note: Exit the procedure immediately if any non-system called function returns an error
;----------------------------------------------
global uterm_format_end

uterm_format_end:
	
	;\e[0m
	mov rdi, '0'
	call uterm_format
	test rdx, rdx
	jne .end
	
	xor rdx, rdx
	
.end:
	ret



