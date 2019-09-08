;----------------------------------------------
; initkfs, 2019
; Prints general-purpose registers values
; Params (1): printf format specifier (%s, %d, etc)
; Calls: str_printf
; Note: Exit immediately if any non-system called function returns an error
; Note: The rsp register is not included in the printout
; WARNING: Since this is a macro and there are many string specifiers, the argument IS NOT validated.
;----------------------------------------------
global debug_print_reg

%macro debug_print_reg 1

%ifstr %1 
%else 
	%error Cannot print registers for debugging. A macro expects a string format identifier for printf, for example '%s', but received: %1
	jmp %%macroEnd
%endif

%%macroStart:

    push rdi
	push rsi
	
	push rbp
	mov rbp, rsp
	sub rsp, 34						; stack allocation on 34 bytes
	and rsp, -16					; stack align
	
	mov [rbp - 34],  rdi			; save 8 byte from rdi
	mov [rbp - 26],  rsi			; save 8 byte from rsi
	mov [rbp - 18],  rdx			; save 8 byte from rdx
	mov dword [rbp - 10],  'RAX:'	; add first register label, 4 bytes
	mov word [rbp - 6], '  '		; add separators, 2 bytes
	mov word [rbp - 4], %1			; add formatter for printf (%s, %d, etc), 2 bytes
	mov byte [rbp - 2], 10			; add new line
	mov byte [rbp - 1], 0			; add null-byte
	
	%%formatAddr: equ 10
	
	lea rdi, [rbp - %%formatAddr]	; move address of formatted string to rdi.
	mov rsi, rax					; print value from rax
	xor rdx, rdx					; value is not float
	call str_printf					; print RAX value
	test rdx, rdx
	jne %%end
	
	mov dword [rbp - %%formatAddr], 'RDI:'
	mov rsi, [rbp - 34]
	call str_printf
	test rdx, rdx
	jne %%end
	
	mov dword [rbp - %%formatAddr], 'RSI:'
	mov rsi, [rbp - 26]
	call str_printf
	test rdx, rdx
	jne .end
	
	mov dword [rbp - %%formatAddr], 'RDX:'
	mov rsi, [rbp - 18]
	call str_printf
	test rdx, rdx
	jne %%end
	
	mov dword [rbp - %%formatAddr], 'RCX:'
	mov rsi, rcx
	call str_printf
	test rdx, rdx
	jne %%end
	
	mov dword [rbp - %%formatAddr], 'RBX:'
	mov rsi, rbx
	call str_printf
	test rdx, rdx
	jne %%end

	mov dword [rbp - %%formatAddr], 'R8: '
	mov rsi, r8
	call str_printf
	test rdx, rdx
	jne %%end
	
	mov dword [rbp - %%formatAddr], 'R9: '
	mov rsi, r9
	call str_printf
	test rdx, rdx
	jne %%end
	
	mov dword [rbp - %%formatAddr], 'R10:'
	mov rsi, r10
	call str_printf
	test rdx, rdx
	jne %%end
	
	mov dword [rbp - %%formatAddr], 'R11:'
	mov rsi, r11
	call str_printf
	test rdx, rdx
	jne %%end
	
	mov dword [rbp - %%formatAddr], 'R12:'
	mov rsi, r12
	call str_printf
	test rdx, rdx
	jne %%end
	
	mov dword [rbp - %%formatAddr], 'R13:'
	mov rsi, r13
	call str_printf
	test rdx, rdx
	jne %%end
	
	mov dword [rbp - %%formatAddr], 'R14:'
	mov rsi, r14
	call str_printf
	test rdx, rdx
	jne %%end
	
	mov dword [rbp - %%formatAddr], 'R15:'
	mov rsi, r15
	call str_printf
	test rdx, rdx
	jne %%end

	xor rdx, rdx

%%end:	
	mov rsp, rbp
	pop rbp
	
	pop rsi
	pop rdi
	
%%macroEnd:

%endmacro

