; errno=850
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
	jp .unknownCompareError
	jc .less
	jz .equals
	
.greater:
	mov rax, 1
	jmp .result
	
.less:
	mov rax, -1
	jmp .result
	
.equals:
	mov rax, 0
	jmp .result
	
.result:
	xor rdx, rdx
	jmp .end
	
.unknownCompareError: 
	mov rdx, 851
	
.end:
	ret
;----------------------------------------------
;			procedure "num_cmpd" end
;----------------------------------------------
