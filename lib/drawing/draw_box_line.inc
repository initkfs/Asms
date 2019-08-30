;----------------------------------------------
; initkfs, 2019
;
; Prints a line with the edges across the entire width of the terminal and a line break after
; WARNING! The procedure assumes that all characters are three bytes long
; See: https://en.wikipedia.org/wiki/Box-drawing_character
;
; Params:
; RDI, left corner symbol
; RSI, center symbol
; RDX, right corner symbol
;
; Example:
; 	mov rdi, '╔'
;	mov rsi, '═'
;	mov rdx, '╗'	
;	call draw_box_line ; ╔══════╗
;
; Calls: uterm_width, sys_writebs, sys_writeln
; Note: Exit the procedure immediately if any non-system called function returns an error
;----------------------------------------------
global draw_box_line

draw_box_line:

	push rax
	push rdi
	push rsi
	push rcx
	
	push r8
	push r9
	push r10
	
	mov r8, rdi		; save left corner symbol
	mov r9, rsi		; save center symbol
	mov r10, rdx	; save right corner symbol
	
	call uterm_width
	test rdx, rdx
	jnz .end
	
	mov rsi, 3		; graphics characters consist of 3 bytes
	
.printLeftCorner:

	lea rdi, [r8]

	call sys_writebs
	test rdx, rdx
	jnz .end

.printCenterLine:

	mov rcx, rax	; set terminal width as counter
	dec rcx			; sub left corner
	dec rcx			; sub right corner, or sub rcx, 2
	
	lea rdi, [r9]

.printLine:

	call sys_writebs
	test rdx, rdx
	jnz .end
	
	loop .printLine
	
.printRightCorner:
	
	lea rdi, [r10]

	call sys_writebs
	test rdx, rdx
	jnz .end

.printLineBreak:

	call sys_writeln
	test rdx, rdx
	jnz .end
	
	xor rdx, rdx

.end:

	pop r10
	pop r9
	pop r8
	
	pop rcx
	pop rsi
	pop rdi
	pop rax

	ret

