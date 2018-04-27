; initkfs, 2018
; Euclidean algorithm implementation
; ---------------------
%include "./../lib/sys/sys_exit.inc"
%include "./../lib/sys/sys_readin.inc"
%include "./../lib/sys/sys_write.inc"
%include "./../lib/string/str_printf.inc"
%include "./../lib/num/num_from_string.inc"
%include "./../lib/string/str_length.inc"

section .data
resultFormat: db "GCD=%ld", 10, 0
notPositive: db "Number must be positive", 10, 0
notEmpty: db "Number cannot be empty", 10, 0

READ_CHAR_COUNT equ 10

section .bss
; buffers for readin
num1: resq 1
num2: resq 1

section .text

global main

main:

readFirst:  
   sys_readin num1, READ_CHAR_COUNT
   mov rdi, num1
   call toNumber
   mov [num1], rax

readSecond:   
   sys_readin num2, READ_CHAR_COUNT
   mov rdi, num2
   call toNumber
   mov [num2], rax

leftGreater:
    mov rax, [num1]
    mov rcx, [num2]
    cmp rax, rcx
    jl rightGreater  
    jmp while   
    
rightGreater:
    xchg rax, rcx ; swap registers

; now a (rax) = larger number, b (rcx) = smaller number
while:
    xor rdx, rdx	; prevent error from div
    div rcx			; rax - result, rcx - remainder
    mov rax, rcx	; a = b
    mov rcx, rdx	; b = remainder
   
    cmp rcx, 0		; while(b != 0)
    jne while		; 
 
result:   
    str_printf resultFormat, rax
    jmp end

toNumber:
   cmp byte [rdi], 10 ; check value is not empty
   jne .convertNumber
   sys_write notEmpty
   sys_exit 1
   
.convertNumber:
   num_from_string rdi
   cmp rax, 0 ; check value is larger then zero
   jg .returnNumber
   sys_write notPositive
   sys_exit 1
.returnNumber:
   ret

end:
sys_exit
