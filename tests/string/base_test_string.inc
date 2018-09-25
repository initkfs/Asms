; initkfs, 2018
; ---------------------
%include "lib/string/str_length.inc"

; include last
%include "tests/base_test.inc"

section .data
string1: db "Hello,",10, 0
string1Size: dq 7
string2: db " world!", 10, 0
string2Size: dq 8

string1And2Concat: db "Hello, world!", 10, 0
string1And2Size: dq 14

section .text
