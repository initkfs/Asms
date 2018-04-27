; initkfs, 2018
; ---------------------
%macro str_length 1 ; 1 - target string, result in rax

%%STRING_END  equ 0 ; null-byte, end of a string

push rdx
push rsi
push rcx

xor rdx, rdx
xor rcx, rcx    

mov rsi, %1 ; target string

%%length:
     mov dl, byte [rsi + rcx]
     cmp dl, %%STRING_END
     je %%result
     inc rcx
     jmp %%length

%%result:
mov rax, rcx

pop rcx
pop rsi
pop rdx

%endmacro

