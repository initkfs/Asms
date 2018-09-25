;----------------------------------------------
; initkfs, 2018
; procedure "dt_day_bydate"
; RDI: Year, RSI: Month, RDX: Day
; Result in RAX: day, starts with 0 - Sunday, or error -1
; https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week
; Schwerdtfeger's method
;----------------------------------------------
global dt_day_bydate

dt_day_bydate:

	enter 16, 0
	
	mov rcx, rdx;	
	
	;rdi - year
	;rsi - month
	;rcx - day
	
	;check year
	test rdi, rdi
	jle .error
	cmp rdi, 2100
	jg .error
	
	;check month
	test rsi, rsi
	jle .error
	cmp rsi, 12
	jg .error
	
	;check day
	test rcx, rcx
	jle .error
	cmp rcx, 31
	jg .error
	
	cmp rsi, 3
	jge .monthGreater3
	
.monthLess3:
	; c =  floor ((y - 1) / 100)
	mov rax, rdi
	dec rax
	movq xmm0, rax
	
	; g = y - 1 - 100c
	mov rax, rdi
	dec rax
	mov r9, rax
	
	jmp .calculateC
	
.monthGreater3:
	; c = floor y / 100
	movq xmm0, rdi
	
	; g = y - 100c
	mov r9, rdi
	
.calculateC:
	mov rax, 100
	movq xmm1, rax
	divsd xmm0, xmm1
	roundsd xmm0, xmm0, 9 ; c == xmm0
	cvtsd2si rax, xmm0 ; convert float to integer
	mov r8, rax ; c == r8
	
.calculateG:
	mov rax, r8
	mov r10, 100
	mul r10
	sub r9, rax ; g == r9

.setE:	
;	m	1	2	3	4	5	6	7	8	9	10	11	12
;   e	0	3	2	5	0	3	5	1	4	6	2	4
	mov [rbp - 1], byte 0
	mov [rbp - 2], byte 3
	mov [rbp - 3], byte 2
	mov [rbp - 4], byte 5
	mov [rbp - 5], byte 0
	mov [rbp - 6], byte 3
	mov [rbp - 7], byte 5
	mov [rbp - 8], byte 1
	mov [rbp - 9], byte 4
	mov [rbp - 10], byte 6
	mov [rbp - 11], byte 2
	mov [rbp - 12], byte 4
	
	mov r12, rsi
	neg r12
	movzx r11, byte [rbp + r12] ; r11 == e
	
;	c mod 4	  0 	1	2	3
;       f	  0 	5	3	1
	mov rax, r8
	mov r12, 4
	xor rdx, rdx
	div r12
	mov rax, rdx 

.setForGregorian:
	cmp rax, 0
	je .setF0
	cmp rax, 1
	je .setF5
	cmp rax, 2
	je .setF3
	cmp rax, 3
	je .setF1
	jmp .error

.setF0:
	xor r12, r12
	jmp .calculateDay
.setF5:
	mov r12, 5
	jmp .calculateDay
.setF3:
	mov r12, 3
	jmp .calculateDay
.setF1:
	mov r12, 1
	
.calculateDay:	
	; w = (d + e + f + g + floor(g/4)) mod 7
	movq xmm0, r9
	mov rax, 4
	movq xmm1, rax
	divsd xmm0, xmm1
	roundsd xmm0, xmm0, 9 ; c == xmm0
	cvtsd2si rax, xmm0
	
	mov r13, rax
	add r13, rcx
	add r13, r11
	add r13, r12
	add r13, r9
	
	mov rax, r13
	mov r14, 7
	div r14
	mov rax, rdx
	
	xor rdx, rdx
	jmp .end

.error: 
	mov rax, -1
	
.end:
	leave
	ret
;----------------------------------------------
;			procedure "dt_day_bydate" end
;----------------------------------------------
