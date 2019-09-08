;----------------------------------------------
; initkfs, 2019
;
; Prints a empty vertical box sides (left and right) across the entire width of the terminal window. A space is printed between the sides.
; See: https://en.wikipedia.org/wiki/Box-drawing_character
;
; Calls: draw_box_sidestr
; Note: Exit the procedure immediately if any non-system called function returns an error
;----------------------------------------------
global draw_box_sides

draw_box_sides:

	push rdi

	push rbp
	mov rbp, rsp
	sub rsp, 2
	and rsp, -16

	mov [rbp - 2], byte ' '
	mov [rbp - 1], byte 0x0
	lea rdi, [rbp - 2]
	call draw_box_sidestr
	test rdx, rdx
	jnz .end
	
	xor rdx, rdx
	
.end:
	mov rsp, rbp
	pop rbp

	pop rdi
	ret
