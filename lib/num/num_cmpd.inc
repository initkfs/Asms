;----------------------------------------------
; initkfs, 2018
; procedure "num_cmpd"
; RDI - first number, RSI - second number
; (1 == 1) == 0
; (1 < 2) == -1
; (2 > 1) == 1
; error\NaN\etc == -2
; Result in RAX
;----------------------------------------------
global num_cmpd

num_cmpd:

	movd xmm0, edi
	movd xmm1, esi
	comiss xmm0, xmm1
	jp .error
	jc .less
	jz .equals
	
.greater:
	mov rax, 1
	jmp .end
	
.less:
	mov rax, -1
	jmp .end
	
.equals:
	mov rax, 0
	jmp .end
	
.error: 
	mov rax, -2
	
.end:
	ret
;----------------------------------------------
;			procedure "num_cmpd" end
;----------------------------------------------
