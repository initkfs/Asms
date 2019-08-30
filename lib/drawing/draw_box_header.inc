;----------------------------------------------
; initkfs, 2019
;
; Prints the top side of the box across the entire width of the terminal and a line break after
; See: https://en.wikipedia.org/wiki/Box-drawing_character
; Example:
;	call draw_box_header ; ╔═════╗
;
; Calls: draw_box_line
; Note: Exit the procedure immediately if any non-system called function returns an error
;----------------------------------------------
global draw_box_header

draw_box_header:

	push rdi
	push rsi
	
	mov rdi, '╔'
	mov rsi, '═'
	mov rdx, '╗'
	
	call draw_box_line
	test rdx, rdx
	jnz .end
	
	xor rdx, rdx

.end:
	
	pop rsi
	pop rdi

	ret

