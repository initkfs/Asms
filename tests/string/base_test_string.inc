; initkfs, 2018
; ---------------------
; include last
%include "tests/base_test.inc"

section .data
string1: db "Hello",10, 0
string1NotContains: db "b", 0
string1FirstLetter: db "H", 0
string1LastLetter: db "o", 0
string1LastLetterPosition: dq 4
string1Size: dq 6
string2: db " world!", 10, 0
string2Size: dq 8

string1And2Concat: db "Hello world!",10, 0
string1And2Size: dq 13

stringEqualsWithString1: db "Hello",10, 0
stringConcatWithString1: db "HelloHello", 10,0

string1SearchWord: db "llo", 0
string1SearchWordIndex: dq 2

string1EndWord: db "lo", 10, 0
string1EndWordIndex: dq 2

section .text
