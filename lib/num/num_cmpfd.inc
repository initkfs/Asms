; errno=800
;----------------------------------------------
; initkfs, 2018
; procedure "num_cmpfd"
; Compare as floating point numbers
; Params:
; RDI, first number
; RSI, second number
; Example:
;	mov rdi, __float64__(3.2001)
;	mov rsi, __float64__(3.2)
;	call num_cmpd ; 1 in RAX
;
; Returns: RAX
; if (1num == 1num) return 0
; if (1num < 2num) return -1
; if (2num > 1num) return 1
; Error: if result is a not valid number (NaN) or a comparison error occurred
;----------------------------------------------
global num_cmpfd

num_cmpfd:

	;TODO save registers
	movq xmm0, rdi
	movq xmm1, rsi
	comisd xmm0, xmm1
	jp .errInvalidCompareResult
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
	
.errInvalidCompareResult: 
	mov rdx, 801
	
.end:
	ret
	
