;----------------------------------------------
; initkfs, 2018
; procedure "str_is_blank"
; Params: 
; RDI, byte symbol
; Returns: RAX, 1 if symbol is blank symbol, or 0
;----------------------------------------------
global str_is_blank

str_is_blank:
	
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
	xor rax, rax
	xor rdx, rdx
	jmp .end

.spaceFound:
	xor rax, rax
	inc rax ;mov rax, 1
	xor rdx, rdx
	
.end:
	ret
;----------------------------------------------
;			procedure "str_is_space" end
;----------------------------------------------


