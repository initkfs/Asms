; errno=500
; array_sort
;  
; initkfs, 2018
; RDI: array address
; Calls: array_get, array_set
;----------------------------------------------
global array_sort
;	int temp;
;	for (int i = 1; i < data.length; i++) {
;		for (int j = i; j > 0; j--) {
;			if (data[j] < data[j - 1]) {
;				temp = data[j];
;				data[j] = data[j - 1];
;				data[j - 1] = temp;
;		}
;	}
array_sort:

	push rax
	push rcx
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	
	call array_count
	test rdx, rdx
	jne .end
	mov rcx, rax ; save array size
	
	mov r8, 1 ; r8, outer loop counter, i = 1
.outerLoop:
	
	mov r9, r8 ; r9 - inner loop counter,  j = i
.innerLoop:

	mov rsi, r9
	call array_get
	test rdx, rdx
	jne .end
	mov r10, rax ; r10 = data[j]
	
	dec rsi
	mov r11, rsi ; r11 = j - 1
	call array_get
	test rdx, rdx
	jne .end
	
	mov r12, rax ; r12 = data[j - 1]
	
	cmp r10, r12
	jg .continueInnerLoop

; 	swap variables
;	data[j] = data[j - 1];
;	data[j - 1] = temp;
	mov rsi, r9
	mov rdx, r12
	call array_set
	
	mov rsi, r11
	mov rdx, r10
	call array_set
	test rdx, rdx
	jne .end

.continueInnerLoop:
	dec r9
	test r9, r9
	jg .innerLoop

.continueOuterLoop:	
	inc r8
	cmp r8, rcx
	jl array_sort.outerLoop
	
	xor rdx, rdx
	jmp .end
	
.end:
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rcx
	pop rax
	ret
