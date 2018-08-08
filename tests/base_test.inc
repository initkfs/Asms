; initkfs, 2018
; ---------------------

section .data
exitFormat: db "ERROR_CODE: %d", 10, 0
lineFormat: db "LINE: %d", 10, 0
fileFormat: db "Failed: %s", 10, 0

numFormat: db "number=%d", 10, 0

actualNumFormat: db "Actual: %d, expected: %d", 10, 0

extern printf

section .data
file1: dq __FILE__

section .text

global printInfo

; RAX - value , RDI - format
printInfo:
	
	;side effect, save all
	push rdi
	push rsi
	push rax
	push rdx
	
	mov rsi, rax
	xor rax, rax ; prevent segfault
	call printf

.end:
	pop rdx
	pop rax
	pop rsi
	pop rdi
	ret
	
global printNum
printNum:

	push rdi
	mov rdi, numFormat
	call printInfo
.end: 
	push rdi
	ret

global printFailInfo
; RAX - exit code, rdi - line, rsi - file path
printFailInfo:

	push rdx
	push rdi
	push rsi
	
	mov rdx, rdi ; save line
	
	mov rdi, exitFormat
	call printInfo

	mov rax, rdx
	mov rdi, lineFormat
	call printInfo
	
	mov rax, rsi
	mov rdi, fileFormat
	call printInfo
.end:
	pop rsi
	pop rdi
	pop rdx
	ret


global assertNumeric
; RAX - actual, RDX - expected
assertNumeric:
	push rax
	push rdx
	push rdi
	
	cmp rax, rdx
	jne .assertFailed
	
	jmp .end

.assertFailed:
	mov rdi, actualNumFormat
	call printInfo

.end:
	pop rdi
	pop rdx
	pop rax
	ret











