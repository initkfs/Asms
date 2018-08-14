;----------------------------------------------
; initkfs, 2018
; procedure "num_reverse"
; RDI - number
; Result in RAX
;----------------------------------------------
global num_reverse

num_reverse:
	; int reverse = 0;
	; while(number != 0){
	;  reverse = reverse*10 + number%10; 
	;  number = number/10;
	;}
	
	push rcx
	push rdx
	push r8
	push r9
	
	cmp rdi, 0
	jl .error
	
	mov r8, 0 ; r8 == reverse
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
	
	cmp rcx, 0
	jne .iterate
	
	mov rax, r8
	jmp .end
.error: 
	mov rax, -1
	
.end:
	pop r9
	pop r8
	pop rdx
	pop rcx
	ret
;----------------------------------------------
;			procedure "num_reverse" end
;----------------------------------------------
