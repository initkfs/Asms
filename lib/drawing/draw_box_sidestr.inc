;----------------------------------------------
; initkfs, 2019
;
; Prints the sides of the box with a string in the middle. If the string cannot fit exactly in the middle, then the left indent will be increased. If the string is larger than the terminal width, then it will be truncated
; See: https://en.wikipedia.org/wiki/Box-drawing_character
; Params:
;	RDI, string memory address
;
; Example:
;	mov rdi, source 		; where source is address of "Hello world" string
;	call draw_box_sidestr	; ║     Hello world     ║
;
; Calls: str_length, uterm_width, sys_writeb, sys_writebs, sys_writestr
; Macros: push64wr, pop64wr
; Note: Exit the procedure immediately if any non-system called function returns an error
;----------------------------------------------
global draw_box_sidestr

draw_box_sidestr:

	push64wr

	mov r8, rdi			; save string address

	call str_length
	test rdx, rdx
	jnz .end

	mov r9, rax			; save string length

	call uterm_width
	test rdx, rdx
	jnz .end

	mov r10, rax		; save terminal width
	dec r10
	dec r10				; remove two characters from the edges of box

	cmp r9, r10			; compare string length and terminal width
	jl .calculateStringIndents

.cutString:
	mov r9, r10			; set string length as terminal width without edges

.calculateStringIndents:
	mov rax, r10		; terminal width without edges
	sub rax, r9			; subtract string length

	mov r11, rax		; save two indents width

	xor rdx, rdx
	mov r12, 2
	idiv r12			; width without edges - string length / 2

	mov r12, rax		; save string indents width

	test rdx, rdx
	jz .printLeftCorner

.paddStringIndent:
	mov rax, r11		; two indents width
	sub rax, r12		; subtract less indent

.printLeftCorner:
	call .printCorner
	test rdx, rdx
	jnz .end

	test rax, rax
	jz .printMainString

	mov rcx, rax
	test rcx, rcx
	jle .printMainString
	mov rdi, ' '
.printLeftIndent:
	call sys_writeb
	test rdx, rdx
	jnz .end

	loop .printLeftIndent

	xor rsi, rsi
.printMainString:
	mov rdi, r8
	mov rsi, r9
	call sys_writestr
	test rdx, rdx
	jnz .end

	mov rdi, ' '
	mov rcx, r12
	test rcx, rcx
	jle .printRightCorner
.printRightIndent:
	call sys_writeb
	test rdx, rdx
	jnz .end

	loop .printRightIndent

.printRightCorner:
	call .printCorner
	test rdx, rdx
	jnz .end

	xor rdx, rdx
	jmp .end

.printCorner:
	push rdi
	push rsi
	mov rdi, '║'
	lea rdi, [rdi]
	mov rsi, 3			; graphics character must be 3 bytes long
	call sys_writebs
..@end:
	pop rsi
	pop rdi
	ret

.end:
	pop64wr
	ret
