;----------------------------------------------
; initkfs, 2019
; Restores ONLY working registers, i.e. all registers except RDX, which is used to save errors
;----------------------------------------------
%macro pop64wr 0
	
	pop rax
	pop64wrmin

%endmacro
