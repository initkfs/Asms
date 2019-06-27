; errno=1000
;----------------------------------------------
; initkfs, 2018
; procedure "str_printf"
; Params: 
; RDI, memory address of string format
; RSI, target value 
; RDX, 1 is a float value
; Example:
;	mov rdi, resultFormat ; "RESULT=%f"
;	lea rax, [rel num] ; dq 565.7, prevent PIE error
;	mov rsi, [rax]
;	mov rdx, 1 ; float number
;	call str_printf ; RESULT=565.700000
;
; Calls: extern printf
; Error: if an error occurred while calling the system printf
;
; Note: 
; Many registers are preserved for the prevention of side effects
;
; https://stackoverflow.com/questions/6212665/why-is-eax-zeroed-before-a-call-to-printf/6212835#6212835
; https://stackoverflow.com/questions/20594800/printf-float-in-nasm-assembly-64-bit
; d or i	Signed decimal integer
; u	Unsigned decimal integer
; o	Unsigned octal
; x	Unsigned hexadecimal integer,	7fa
; X	Unsigned hexadecimal integer (uppercase),	7FA
; f	Decimal floating point, lowercase,	392.65
; F	Decimal floating point, uppercase,	392.65
; e	Scientific notation (mantissa/exponent), lowercase,	3.9265e+2
; E	Scientific notation (mantissa/exponent), uppercase,	3.9265E+2
; g	Use the shortest representation: %e or %f,	392.65
; G	Use the shortest representation: %E or %F,	392.65
; a	Hexadecimal floating point, lowercase,	-0xc.90fep-2
; A	Hexadecimal floating point, uppercase,	-0XC.90FEP-2
; c	Character,	a
; s	String of characters,	sample
; p	Pointer address,	b8000000
; n	Nothing printed.
; %	A % followed by another % character will write a single % to the stream.	%
; Length & Description
; l argument is interpreted as a long int or unsigned long int for integer specifiers (i, d, o, u, x and X), and as a wide character or wide character string for specifiers c and s.
; h argument is interpreted as a short int or unsigned short int (only applies to integer specifiers: i, d, o, u, x and X).
; L argument is interpreted as a long double (only applies to floating point specifiers: e, E, f, g and G).
;----------------------------------------------
global str_printf

extern	printf

str_printf:
	;push rdx - error code
	push rax
	push rcx
	push rsi
	push rdi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15

	cmp rdx, 1
	je .preparePrintFloat
	
	xor rax, rax ; segfault without reset 
	jmp .callPrintf
	
.preparePrintFloat:
	mov rax, 1
	movq xmm0, qword rsi
	
.callPrintf:
	call printf WRT ..plt ;for PIE
	test rax, rax
	jl .errCallPrintfError
	xor rdx, rdx
	jmp .end
	
.errCallPrintfError:
	mov rdx, 1001

.end:
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rdi    
	pop rsi        
	pop rcx
	pop rax
	ret
