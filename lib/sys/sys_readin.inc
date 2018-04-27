; initkfs, 2018
; ---------------------
%macro sys_readin 2 ; 1 - buffer with result, 2 - buffer char size, buffer is variable

%%SYS_READ equ 0 ; linux sys_read, rax: 0, rdi: unsigned int fd, rsi: char *buf , rdx: size_t count
%%STDIN    equ 0 ; linux stdin, 0

push rax
push rdi
push rsi
push rdx

mov rax, %%SYS_READ
mov rdi, %%STDIN
mov rsi, %1 ; buffer
mov rdx, %2 ; buffer char size
  
syscall

pop rdx
pop rsi
pop rdi
pop rax

%endmacro
