; errno=1580
;----------------------------------------------
; initkfs, 2019
; 
; Prints string to stdout. The string must end with a null byte
; RDI: memory address of string with null-byte
; RSI: number of characters to print, or 0 for full string. Be careful with utf.
;
; Example:
; 	xor rsi, rsi
; 	mov rdi, source
; 	call sys_writestr
;
; Calls: str_length, sys_write
; Error: if string size is negative
; Error: if string size is larger than the string
; Error: if string length is zero, ex: string: db "", 0 will throw an error
; Note: Exit the procedure immediately if any non-system called function returns an error
; ---------------------
global sys_writestr:

sys_writestr:

	push rsi
	push rax

	test rsi, rsi
	jl .errStringSizeNegative
	
	call str_length
	test rdx, rdx
	jne .end
	
	test rax, rax
	je .errStringSizeIsZero
	
	cmp rsi, rax
	jg .errStringSizeGreater
	
	test rsi, rsi
	jg .print
	
	mov rsi, rax
	
.print:
	call sys_write
	test rdx, rdx
	jne .end
	
	xor rdx, rdx
	jmp .end
	
.errStringSizeNegative:
	mov rdx, 1581
	jmp .end

.errStringSizeGreater:
	mov rdx, 1582
	jmp .end

.errStringSizeIsZero:
	mov rdx, 1583
	jmp .end
	
.syscallSysWriteError:
	mov rdx, 1584

.end:
	pop rax
	pop rsi
	ret
