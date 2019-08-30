;----------------------------------------------
; initkfs, 2019
;
; Prints a horizontal line across the entire width of the terminal window and a line break after. Printing occurs with the '═'(U+2550) symbol
; See: https://en.wikipedia.org/wiki/Box-drawing_character
;
; Calls: uterm_width, sys_writebs, sys_writeln
; Note: Exit the procedure immediately if any non-system called function returns an error
;----------------------------------------------
global draw_hline

draw_hline:

	push rdi
	push rsi
	push rcx
	push rax

	call uterm_width
	test rdx, rdx
	jnz .end

	mov rdi, '═'
	lea rdi, [rdi]
	mov rsi, 3		; '═' consists of 3 bytes: 0xe2 0x95 0x94
	
	mov rcx, rax	; set counter for loop command

.printLine:

	call sys_writebs
	test rdx, rdx
	jnz .end
	
	loop .printLine
	
.printLineBreak:

	call sys_writeln
	test rdx, rdx
	jne .end
	
	xor rdx, rdx

.end:
	
	pop rax
	pop rcx
	pop rsi
	pop rdi
	
	ret

