;----------------------------------------------
; initkfs, 2018
; procedure "math_cos"
; RAX - radians
; Result in RAX
;----------------------------------------------
global math_sin

math_cos:

	enter 16, 0
	mov [rbp - 8], rax
	
	finit
	fld qword [rbp - 8]

	fcos
	fst qword [rbp - 16]
	mov rax, qword [rbp - 16]
.end:
	leave
	ret
;----------------------------------------------
;			procedure "math_cos" end
;----------------------------------------------
