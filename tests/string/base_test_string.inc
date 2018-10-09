; initkfs, 2018
; ---------------------
%include "lib/string/str_length.inc"
%include "lib/string/str_copy.inc"
%include "lib/string/str_repeat.inc"
%include "lib/string/str_cmp.inc"
%include "lib/string/str_search.inc"
%include "lib/string/str_end.inc"

; include last
%include "tests/base_test.inc"

section .data
string1: db "Hello",10, 0
string1Size: dq 6
string2: db " world!", 10, 0
string2Size: dq 8

string1And2Concat: db "Hello world!",10, 0
string1And2Size: dq 13
stringEqualsWithString1: db "Hello",10, 0

string1SearchWord: db "llo", 0
string1SearchWordIndex: dq 2

string1EndWord: db "lo", 10, 0
string1EndWordIndex: dq 2

section .text
