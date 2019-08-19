; errno=1400
;----------------------------------------------
; initkfs, 2018
; Procedure "bit_unset". Unset k-bit in the number
; Params: 
; RDI, unsigned number
; RSI, bit position, 1 <= n <= 64
; Example:
;	mov rdi, 192 ;11000000
;	mov rsi, 7 
;	call bit_unset ; RAX: 128 (10000000)
;
; Returns: RAX, result number
; Error: if bit position out of bounds
; Calls: bit_1shl
; Note: Exit the procedure immediately if any non-system called function returns an error
; y = x & ~(1<<n)
;----------------------------------------------
global bit_unset

bit_unset:
	push r8
	
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
	not rax
	and rax, rdi
	
	xor rdx,rdx
	jmp .end
	
.errBitNumberIsTooSmall:
	mov rdx, 1402
	jmp .end

.errBitNumberTooLarge:
	mov rdx, 1403
	
.end:
	pop r8
	ret
