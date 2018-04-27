; initkfs, 2018
; ---------------------
%macro sys_write 1-2 -1; 1 - target string, only chars not a number, 2 - string size
; default -1, string length autocalculated

%ifnmacro str_length
    %error Error: not found 'str_length' macros for a string length calculation.
%endif

%%SYS_WRITE   equ 1 ; linux sys_write, 64bit
%%STDOUT      equ 1 ; stdout
%%STRING_END  equ 0 ; null-byte

push rax
push rdi
push rsi
push rdx

mov rsi, %1 ; target string

%if %2 > 0
    mov rdx, %2 ; string size from the parameter
%elif %2 = -1 
    str_length rsi ; calculate string size
	mov rdx, rax   ; mov string size to the rdx
%else
    %error Error: incorrect string length received. Expected positive number.
%endif 

mov rax, %%SYS_WRITE
mov rdi, %%STDOUT

syscall

pop rdx
pop rsi
pop rdi
pop rax

%endmacro
