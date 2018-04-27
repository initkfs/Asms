; initkfs, 2018
; ---------------------
%macro sys_exit 0-1 0 ;default return code: 0

%%SYS_EXIT  equ 60 ; sys_exit linux system call, linux 64 

mov rax, %%SYS_EXIT
mov rdi, %1 ;%rdi - exit code
syscall

%endmacro
