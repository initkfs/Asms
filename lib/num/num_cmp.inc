; errno=800
;----------------------------------------------
; initkfs, 2018
; procedure "num_cmp"
; RDI - first number, RSI - second number
; (1 == 1) == 0
; (1 < 2) == -1
; (2 > 1) == 1
; error\NaN\etc == -2
; Result in RAX
;----------------------------------------------
global num_cmp

num_cmp:

	enter 16, 0
	
	mov [rbp - 8], rdi ; save first number
	mov [rbp - 16], rsi ; save second number
	
	finit
	fld qword [rbp - 8]
	fld qword [rbp - 16]
	
	fcom ; compare st(0) and st(1)
	
	fstsw ax ; save swr to ax
	sahf ; save ax to rflags
	jp .errUnknownFpuError
	jc .greater
	jz .equals
	
.less:
	mov rax, -1
	jmp .result
	
.greater:
	mov rax, 1
	jmp .result
	
.equals:
	xor rax, rax
	jmp .result
	
.result:
	xor rdx, rdx
	jmp .end
	
.errUnknownFpuError: 
	mov rdx, 801

.end:
	leave
	ret
;----------------------------------------------
;			procedure "num_cmp" end
;----------------------------------------------
