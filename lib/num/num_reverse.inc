; errno=700
;----------------------------------------------
; initkfs, 2018
; procedure "num_reverse"
; Params:
; RDI, positive decimal number
; Example:
;	mov rdi, 134
;	call num_reverse ;431 in RAX
;
; Returns: RAX
; Error: if input number is not positive
;----------------------------------------------
global num_reverse

num_reverse:
	; int reverse = 0;
	; while(number != 0){
	;  reverse = reverse*10 + number%10; 
	;  number = number/10;
	;}
	
	push rcx
	push r8
	push r9
	
	test rdi, rdi
	jle .errArgNumberIsNotPositive
	
	xor r8, r8 ; r8 == reverse
	mov rcx, rdi ; rcx == number
.iterate:

	mov r9, 10 ; r9 == 10

	mov rax, r8
	mul r9
	mov r8, rax
	
	mov rax, rcx
	xor rdx, rdx
	div r9
	add r8, rdx
	
	mov rax, rcx
	xor rdx, rdx
	div r9
	mov rcx, rax
	
	test rcx, rcx
	jne .iterate
	
	mov rax, r8
	xor rdx, rdx
	jmp .end

.errArgNumberIsNotPositive:
	mov rdx, 701
	
.end:
	pop r9
	pop r8
	pop rcx
	ret
