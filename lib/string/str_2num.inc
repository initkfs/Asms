; initkfs, 2018
; ---------------------
%macro num_from_string 1 ; target string, result in rax

extern atoi

push rdi

mov rdi, %1

push rbp
mov rbp,rsp
call atoi
leave

pop rdi

%endmacro
