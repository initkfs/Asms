; errno=1600
;----------------------------------------------
; initkfs, 2019
;
; Prints box with header, footer and body of a given length with a string in the middle, across the entire width of the terminal.
; See: https://en.wikipedia.org/wiki/Box-drawing_character
; Params:
;	RDI, string memory address
;	RSI, height in lines before the string
;	RDX, height in lines after the string
;
; Example:
; 	mov rdi, source ; memory address
;	mov rsi, 1
;	mov rdx, 1
;	call draw_box_message ; 
; ╔═════════════╗
; ║             ║ ; <--- before
; ║ Hello world ║ ; <--- string
; ║             ║ ; <--- after
; ╚═════════════╝
; Calls: draw_box_header, draw_box_sides, draw_box_sidestr, draw_box_footer
; Error: if the height before the string is not a positive signed number
; Error: if the height after the string is not a positive signed number
; Note: Exit the procedure immediately if any non-system called function returns an error
;----------------------------------------------
global draw_box_message

draw_box_message:

	push r8
	push rcx

	test rsi, rsi
	jle .errBoxHeightBeforeStringNotPositive

	test rdx, rdx
	jle .errBoxHeightAfterStringNotPositive

	mov r8, rdx

.printBoxHeader:
	call draw_box_header
	test rdx, rdx
	jnz .end

	mov rcx, rsi
.printSidesBeforeMessage:
	call draw_box_sides
	test rdx, rdx
	jnz .end

	loop .printSidesBeforeMessage

.printBoxMessage:
	call draw_box_sidestr
	test rdx, rdx
	jnz .end

	mov rcx, r8
.printBoxAfterMessage:
	call draw_box_sides
	test rdx, rdx
	jnz .end

	loop .printBoxAfterMessage

.printBoxFooter:
	call draw_box_footer
	test rdx, rdx
	jnz .end

	xor rdx, rdx
	jmp .end

.errBoxHeightBeforeStringNotPositive:
	mov rdx, 1601
	jmp .end

.errBoxHeightAfterStringNotPositive:
	mov rdx, 1602

.end:
	pop rcx
	pop r8
	ret
