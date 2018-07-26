;----------------------------------------------
; initkfs, 2018
; procedure "num_cos"
; RAX - radians
; Result in RAX
;----------------------------------------------
global num_cos

num_cos:

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
;			procedure "num_cos" end
;----------------------------------------------
