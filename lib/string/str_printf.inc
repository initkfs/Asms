; initkfs, 2018
; ---------------------
%macro str_printf 2-3 0 ; RDI - format, RSI - target, 1 - is_float

;https://stackoverflow.com/questions/6212665/why-is-eax-zeroed-before-a-call-to-printf/6212835#6212835
;https://stackoverflow.com/questions/20594800/printf-float-in-nasm-assembly-64-bit

extern	printf

;d or i	Signed decimal integer
;u	Unsigned decimal integer
;o	Unsigned octal
;x	Unsigned hexadecimal integer,	7fa
;X	Unsigned hexadecimal integer (uppercase),	7FA
;f	Decimal floating point, lowercase,	392.65
;F	Decimal floating point, uppercase,	392.65
;e	Scientific notation (mantissa/exponent), lowercase,	3.9265e+2
;E	Scientific notation (mantissa/exponent), uppercase,	3.9265E+2
;g	Use the shortest representation: %e or %f,	392.65
;G	Use the shortest representation: %E or %F,	392.65
;a	Hexadecimal floating point, lowercase,	-0xc.90fep-2
;A	Hexadecimal floating point, uppercase,	-0XC.90FEP-2
;c	Character,	a
;s	String of characters,	sample
;p	Pointer address,	b8000000
;n	Nothing printed.
;%	A % followed by another % character will write a single % to the stream.	%

;Length & Description
;l argument is interpreted as a long int or unsigned long int for integer specifiers (i, d, o, u, x and X), and as a wide character or wide character string for specifiers c and s.
;h argument is interpreted as a short int or unsigned short int (only applies to integer specifiers: i, d, o, u, x and X).
;L argument is interpreted as a long double (only applies to floating point specifiers: e, E, f, g and G).


; TODO. Float point:
; num1: dq 175.5
; str_printf resultFormat, [num1], 1

push rdi
push rsi
push rax
push rcx

mov rdi, %1 ; string format to rdi, pass VALUE, not a address
mov rsi, %2 ; target to rsi,  pass VALUE, not a address

%if %3 = 1
	mov rax, 1 ; fix float point printing
	movq xmm0, qword rsi
%else
	xor rax,rax ; segfault without reset 
%endif 

call printf

pop rcx
pop rax
pop rsi
pop rdi

%endmacro
