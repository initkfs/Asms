; initkfs, 2018
; ---------------------
; 1 - target string, 2 - searched, rax: index or -1 if searched not found
%macro str_search 2

%ifnmacro str_length
    %error Error: not found 'str_length' macros.
%endif

section .data

section .bss
	%%targetString: resq 1
	%%pattern: resq 1
	%%stringSize: resq 1
	%%patternSize: resq 1
    
section .text

strSearch:

	push rbx
	push rcx
	push rdi

	mov qword [%%targetString], %1
	mov qword [%%pattern], %2
		
	str_length [%%targetString]
	mov [%%stringSize], rax
	
	str_length [%%pattern]
	mov [%%patternSize], rax
	
	xor rcx, rcx

.iterateString:
	mov rax, [%%patternSize + rcx]
	cmp rax, [%%stringSize]
	jg .patternNotFound
	
	xor rbx, rbx

.searchPattern:
	
	movzx rax, byte [%1 + rbx + rcx] ; get one character from string
	movzx rdi, byte [%2 + rbx]

	cmp rax, rdi
	jne .innerLoopAgain
	
	cmp rcx, [%%stringSize]	; prevent last null byte detection
	jge .patternNotFound 	

	inc rbx
	cmp rbx, [%%patternSize]
	jge .patternFound
	
	jmp .searchPattern

.innerLoopAgain:
	inc rcx
	jmp .iterateString
	
.patternFound:
	mov rax, rcx
	jmp .end
	
.patternNotFound:
	mov rax, 1
	neg rax
	
.end:
	pop rdi
	pop rcx
	pop rbx

%endmacro

