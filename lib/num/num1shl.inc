;----------------------------------------------
; initkfs, 2018
; procedure "num1shl" or  1 << n
; Params: 1 - n-bit in RAX (AL)
; Result in RAX
;----------------------------------------------
global num1shl

num1shl:
	push rcx

	mov cl, al ; required for shl
	mov rax, 1
	shl rax, cl ; 1 << n

.end:
	pop rcx
	ret
;----------------------------------------------
;			procedure "num1shl" end
;----------------------------------------------
