;----------------------------------------------
; initkfs, 2018
; procedure "math_sin"
; RAX - radians
; Result in RAX
;----------------------------------------------
global math_sin

math_sin:

	enter 16, 0
	mov [rbp - 8], rax
	
	finit
	fld qword [rbp - 8]

	fsin
	;fstsw ax ;swr to ax
	;sahf ; swr->ax->EFLAGS
	;js .error
	
	fst qword [rbp - 16]
	mov rax, qword [rbp - 16]
	jmp .end
	
.error:
	mov rax, -1

.end:
	leave
	ret
;----------------------------------------------
;			procedure "math_sin" end
;----------------------------------------------
