; errno=1350
;----------------------------------------------
; initkfs, 2018
; Procedure "bit_set". Set k-bit in the number
; Params: 
; RDI, unsigned number
; RSI, bit position, 1 <= n <= 64
; Example:
;	mov rdi, 1 ;00000001
;	mov rsi, 8
;	call bit_set ; RAX: 129 (10000001)
;
; Returns: RAX, result number
; Error: if input number is not positive
; Error: if bit position out of bounds
; Calls: _bit_1shl_dec
; Note: Exit the procedure immediately if any non-system called function returns an error
; y = x | (1<< (n - 1))
;----------------------------------------------
global bit_set

bit_set:
	push r8
	
	test rdi, rdi
	je .errValueIsNotPositive ; unsigned value, check zero only
	
	cmp rsi, 1
	jl .errBitNumberIsTooSmall
	
	cmp rsi, 64
	jg .errBitNumberTooLarge

	mov r8, rdi
	
	mov rdi, rsi
	call _bit_1shl_dec ; rax: 1 << n - 1
	test rdx, rdx
	jne .end

.test:
	mov rdi, r8 ; restore rdi
	or rax, rdi
	
	xor rdx, rdx
	jmp .end

.errValueIsNotPositive:
	mov rdx, 1351
	jmp .end
	
.errBitNumberIsTooSmall:
	mov rdx, 1352
	jmp .end

.errBitNumberTooLarge:
	mov rdx, 1353
	
.end:
	pop r8
	ret
