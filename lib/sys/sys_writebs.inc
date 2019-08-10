; errno=1590
;----------------------------------------------
; initkfs, 2019
; Prints bytes from register to stdout with the number of bytes to print
; NOTE: The procedure searches for a null byte when storing a string in qword, so the string size should be less by 1
; Params:
; RDI, contains byte characters
; RSI, number of byte characters to print, or 0 for all.
; Example:
; 	mov rdi, '4;6'
;	xor rsi, rsi
;	call sys_writebs ; => 4;6
;
; Calls: sys_write
; Error: if an error occurred while searching for the string length
; Error: if an unsigned numeric overflow occurred while searching for the length of the string
; Note: Exit the procedure immediately if any non-system called function returns an error
;----------------------------------------------
global sys_writebs:

sys_writebs:

	push rsi 
	push rdi
	push r8
	
	mov r8, rdi 		; save characters

	push rbp
	mov rbp, rsp
	sub rsp, 8
	and rsp, -16
	
	mov [rbp - 8 ], r8
	lea rdi, [rbp - 8]
	
	test rsi, rsi
	jne .printWithCounter
	
	xor rax, rax
	xor rcx, rcx
	
.searchNullByte:
	scasb
	jz .setNewStringLengthCounter
	inc rcx
	jo .errSearchStringEndOverflow
	jmp .searchNullByte

.setNewStringLengthCounter:
	mov rsi, rcx
	test rsi, rsi
	jle .errSearchStringCountFailed
	
.printWithCounter:
	lea rdi, [rbp - 8]
	call sys_write
	test rdx, rdx
	jne .end
	
	xor rdx, rdx
	jmp .end

.errSearchStringCountFailed:
	mov rdx, 1591
	jmp .end
	
.errSearchStringEndOverflow:
	mov rdx, 1592
	
.end:
	mov rsp, rbp
	pop rbp
	
	pop r8
	pop rdi
	pop rsi
	ret
