; initkfs, 2018
; ---------------------
%include "lib/sys/sys_exit.inc"
%include "lib/string/str.inc"

section .data
exitFormat: db "ERROR_CODE: %d", 10, 0
lineFormat: db "LINE: %d", 10, 0
fileFormat: db "File: %s", 10, 0

numFormat: db "number=%d", 10, 0
strformat: db "string=%s", 10, 0

actualNumFormat: db "Actual (RAX): %d, expected (R8): %d", 10, 0

section .data
file1: dq __FILE__

section .text

global printInfo

; RAX - value , RDI - format
printInfo:
	push rsi

	mov rsi, rax
	;xor rdx, rdx ; second argument
	call str_printf
.end:
	pop rsi
	ret
	
global printString
printString:
	push rdi
	mov rdi, strformat
	call printInfo
.end:
	pop rdi
	ret
	
global printNum
printNum:

	push rdi
	mov rdi, numFormat
	call printInfo
.end: 
	pop rdi
	ret

global printFailInfo
; RDX - exit code
; RDI - line
; RSI - file path
printFailInfo:

	push rdx
	push rdi
	push rsi
	push r8
	push rax
	
	mov r8, rdi ; save line
	
	mov rax, rdx
	mov rdi, exitFormat
	call printInfo

	mov rax, r8
	mov rdi, lineFormat
	call printInfo
	
	mov rax, rsi
	mov rdi, fileFormat
	call printInfo
.end:
	pop rax
	pop r8
	pop rsi
	pop rdi
	pop rdx
	ret


global assertNumeric
; RAX - actual, R8 - expected
assertNumeric:
	push rax
	push rdi
	push rdx
	
	cmp rax, r8
	jne .assertFailed
	
	jmp .end

.assertFailed:
	mov rdx, r8
	mov rdi, actualNumFormat
	call printInfo

.end:
	pop rdx
	pop rdi
	pop rax
	ret

global testFailed
testFailed:
	mov rdi, -1
	call sys_exit
	ret

global testSuccess
testSuccess:
	mov rdi, 0
	call sys_exit
	ret











