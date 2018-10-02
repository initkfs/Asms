;----------------------------------------------
; initkfs, 2018
; procedure "str_2num"
; Params: 
; RDI - memory address of string. 
; Return: RAX, number string representation
; Calls: extern atoi
; @TODO @FIXME save registers, add errors, etc
;----------------------------------------------
global str_2num:

extern atoi

str_2num:

call atoi

.end
	ret
