; initkfs, 2018
; ---------------------
%macro str_printf 2 ; format, target string

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

push rdi
push rsi
push rax

enter 0,0

mov rdi, %1 ; string format to rdi
mov rsi, %2 ; target to rsi
xor rax,rax ; segfault without reset
call printf

leave

pop rax
pop rsi
pop rdi

%endmacro
