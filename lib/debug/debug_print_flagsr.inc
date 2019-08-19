;----------------------------------------------
; initkfs, 2019
; Prints some RFLAGS values
; Calls: str_printf, bit_is_set 
; Note: Exit immediately if any non-system called function returns an error
; WARNING: Not all flags will be printed
;----------------------------------------------
global debug_print_flagsr

debug_print_flagsr:

    push rdi
	push rsi
	push rax
	push r8
	push r9
	
	pushfq
	pop rax
	
	push rbp
	mov rbp, rsp
	sub rsp, 8
	and rsp, -16
	
	mov word [rbp - 8],  'CF'		; add first register label, 4 bytes
	mov dword [rbp - 6], ': %u'		; add separators, 2 bytes
	mov byte [rbp - 2], 10			; add new line
	mov byte [rbp - 1], 0			; add null-byte

	lea r8, [rbp - 8]
	mov r9, rax
	
	mov rdi, r9
	xor rsi, rsi
	inc rsi							; mov rsi, 1
	call bit_is_set 
	test rdx, rdx
	jne .end

	mov rdi, r8
	mov rsi, rax
	
	call str_printf
	test rdx, rdx
	jne .end
	
	mov word [rbp - 8],  'ZF'
	mov rdi, r9
	mov rsi, 7
	call bit_is_set 
	test rdx, rdx
	jne .end

	mov rdi, r8
	mov rsi, rax
	
	call str_printf
	test rdx, rdx
	jne .end

	mov word [rbp - 8],  'SF'
	mov rdi, r9
	mov rsi, 8
	call bit_is_set 
	test rdx, rdx
	jne .end

	mov rdi, r8
	mov rsi, rax
	
	call str_printf
	test rdx, rdx
	jne .end
	
	mov word [rbp - 8],  'OF'
	mov rdi, r9
	mov rsi, 12
	call bit_is_set 
	test rdx, rdx
	jne .end

	mov rdi, r8
	mov rsi, rax
	
	call str_printf
	test rdx, rdx
	jne .end
	
	xor rdx, rdx
	
.end:
	mov rsp, rbp
	pop rbp
	
	pop r9
	pop r8
	pop rax
	pop rsi
	pop rdi
	
	ret

