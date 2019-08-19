;----------------------------------------------
; initkfs, 2019
; Prints general-purpose registers values as decimal values
; Macros calls: debug_print_reg
; Note: Exit the procedure immediately if any non-system called function returns an error
;----------------------------------------------
global debug_print_regd

debug_print_regd:

	debug_print_reg '%d'

.end:
	ret
