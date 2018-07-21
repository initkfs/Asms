;----------------------------------------------
; initkfs, 2018
; procedure "str_is_space"
; Params: 1 - byte symbol, RDI
;
; Result: RAX, 1 if symbol is space, or 0
;----------------------------------------------
global str_is_space

str_is_space:
	.start:
	
	cmp dil, 0x20 ; " ", whitespace, ASCII 32
	je .spaceFound
	
	cmp dil, 0x09 ; \t, tab, ASCII 9
	je .spaceFound
	
	cmp dil, 0x0A ; \n, new line, ASCII 10
	je .spaceFound
	
	cmp dil, 0x0D ; \r, a carriage return, ASCII 13
	je .spaceFound
	
	cmp dil, 0x00 ; \0, a null byte, ASCII 0
	je .spaceFound
	
	cmp dil, 0x0B; \x0B, a vertical tab, ASCII 11
	je .spaceFound

.spaceNotFound:
	mov rax, 0
	jmp .end

.spaceFound:
	mov rax, 1
	
.end:
	ret
;----------------------------------------------
;			procedure "str_is_space" end
;----------------------------------------------


