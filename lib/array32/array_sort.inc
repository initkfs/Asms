;----------------------------------------------
; array_sort
;  
; initkfs, 2018
; RDI: array address
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

	push rcx
	push rdx

	call array_size
	mov rcx, rax ; save array size
	
	mov r8, 1 ; r8, outer loop counter, i = 1
.outerLoop:
	
	mov r9, r8 ; r9 - inner loop counter,  j = i
.innerLoop:

	mov rsi, r9
	call array_get
	mov r10, rax ; r10 = data[j]
	
	dec rsi
	mov r11, rsi ; r11 = j - 1
	call array_get
	mov r12, rax ; r12 = data[j - 1]
	
	cmp r10, r12
	jg .continueInnerLoop
	
;	data[j] = data[j - 1];
;	data[j - 1] = temp;
	mov rsi, r9
	mov rdx, r12
	call array_set
	
	mov rsi, r11
	mov rdx, r10
	call array_set


.continueInnerLoop:
	dec r9
	cmp r9, 0
	jg .innerLoop

.continueOuterLoop:	
	inc r8
	cmp r8, rcx
	jl array_sort.outerLoop
	
	jmp .end
.error: 
	mov rax, -1
	
.end:
	pop rdx
	pop rcx
	ret
