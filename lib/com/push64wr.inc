;----------------------------------------------
; initkfs, 2019
; Saves ONLY working registers, i.e. all registers except RDX, which is used to save errors
;----------------------------------------------
%macro push64wr 0

	push64wrmin

	push rax

%endmacro
