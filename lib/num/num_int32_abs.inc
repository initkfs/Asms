; errno=1190
;----------------------------------------------
; initkfs, 2018
; procedure "num_int32_abs"
; Params: 
; RDI, target number. The size of the number must be in the range of the 32-bit integer 
; Example:
;	mov rdi, -5
;	call num_abs ; 5 in RAX
;
; Returns: RAX, absolute value of a number
; Calls: num_int32_min, num_int32_max
; Error: if the number is larger than integer 32-bit max value
; Error: if the number is less than integer 32-bit min value
; Note: Exit the procedure immediately if any non-system called function returns an error
;----------------------------------------------
global num_int32_abs

num_int32_abs:

	call num_int32_min
	test rdx, rdx
	jne .end
	
	cmp rdi, rax
	jl .errNumberLessThanAllowed
	
	call num_int32_max
	test rdx, rdx
	jne .end
	
	cmp rdi, rax
	jg .errNumberLargerThanAllowed

	mov rax, rdi
	; rdi >>> 63, top bit isolation
	sar rax, 63
	
	; abs(x) = (x XOR y) - y
	mov rdx, rdi
	xor rdx, rax
	sub rdx, rax

	mov rax, rdx
	xor rdx, rdx
	jmp .end
	
.errNumberLessThanAllowed:
	mov rdx, 1191
	jmp .end
	
.errNumberLargerThanAllowed:
	mov rdx, 1192
	jmp .end
	
.end:
	ret
