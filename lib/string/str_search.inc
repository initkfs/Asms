;----------------------------------------------
; initkfs, 2018
; procedure "str_search"
; Params: 1 - memory address of string, RDI. 2 - memory address of pattern, RSI
; Result: RAX, index of pattern, or -1 if pattern not found
;----------------------------------------------
global str_search

str_search:
	.start:
	
	push rcx
	push rbx
	push r8
	
	; rdi - string address
	; rsi - pattern address
	enter 16, 0 ; two counter 8 byte x 2
	
	call str_length
	mov [rbp - 16], rax ; string length counter
	
	xchg rdi, rsi
	
	call str_length
	mov [rbp - 8], rax ; pattern counter
	
	xchg rdi, rsi

.strSearch:
	xor rcx, rcx

.iterateString:

	xor rax, rax
	add rax, [rbp - 8] ; pattern size
	add rax, rcx

	cmp rax, [rbp - 16] ; compare pattern size + counter with string size
	jg .patternNotFound
	
	xor rax, rax
	xor rbx, rbx

.searchPattern:

	; TODO remove r8
	xor r8, r8
	add r8, rbx
	add r8, rcx

	mov al, byte [rdi + r8] ; char from string
	cmp al, byte [rsi + rbx] ; compare with char from pattern
	jne .innerLoopAgain
	
	cmp rcx, [rbp - 16]	; compare with string size, prevent last null byte detection
	jge .patternNotFound 	

	inc rbx
	cmp rbx, [rbp - 8] ; compare with pattern size
	jge .patternFound
	
	jmp .searchPattern

.innerLoopAgain:
	inc rcx
	jmp .iterateString
	
.patternFound:
	mov rax, rcx
	jmp .end
	
.patternNotFound:
	mov rax, -1
	
.end:
	leave
	
	pop r8
	pop rbx
	pop rcx
	
	ret
;----------------------------------------------
;			procedure "str_search" end
;----------------------------------------------


