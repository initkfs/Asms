; errno=1300
;----------------------------------------------
; initkfs, 2018
; Procedure "bit_is_set". Check bit is set in the unsigned number
; Params: 
; RDI, unsigned number
; RSI, bit position, 1 <= n <= 64
; Example:
;	mov rdi, 128 ; 10000000
;	mov rsi, 8
;	call bit_is_set ; RAX: 1
;
; Returns: RAX, 1 if bit is set or 0 otherwise
; Error: if input number is not positive
; Error: if bit position out of bounds
; Calls: bit_1shl
; Note: Exit the procedure immediately if any non-system called function returns an error
; x & (1<< (n - 1))) != 0 
;----------------------------------------------
global bit_is_set

bit_is_set:
	push r8

	test rdi, rdi
	je .errValueIsNotPositive
	
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
	and rax, rdi
	jz .bitNotSet

.bitIsSet:
	xor rdx, rdx
	xor rax, rax
	inc rax
	jmp .end
	
.bitNotSet:
	xor rax, rax
	xor rdx, rdx
	jmp .end

.errValueIsNotPositive:
	mov rdx, 1301
	jmp .end
	
.errBitNumberIsTooSmall:
	mov rdx, 1302
	jmp .end

.errBitNumberTooLarge:
	mov rdx, 1303
	
.end:
	pop r8
	ret
