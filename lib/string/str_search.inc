;----------------------------------------------
; initkfs, 2018
; procedure "str_search"
; Params: 
; Strings must end with a null character
; RDI, memory address of string
; RSI, memory address of pattern
; Example:
;	mov rdi, string
;	mov rsi, pattern
;	call str_search
;
; Returns: RAX, index of pattern, or -1 if pattern not found
; Calls: str_length
; Note: Exit the procedure immediately if any non-system called function returns an error
;----------------------------------------------
global str_search

str_search:

	push rcx
	push rbx
	push r8
	
	; rdi - string address
	; rsi - pattern address
	enter 16, 0 ; two counter 8 byte x 2
	
	call str_length
	test rdx, rdx
	jne .end
	
	mov [rbp - 16], rax ; string length counter
	
	xchg rdi, rsi
	
	call str_length
	test rdx, rdx
	jne .end
	
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
	xor rdx, rdx
	jmp .end
	
.patternNotFound:
	mov rax, -1
	xor rdx, rdx
	
.end:
	leave
	
	pop r8
	pop rbx
	pop rcx
	
	ret
;----------------------------------------------
;			procedure "str_search" end
;----------------------------------------------


