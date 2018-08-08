; initkfs, 2018
; ---------------------

; include last
%include "tests/base_test.inc"

section .data
array1element: dq 8
array2element: dq 6
array3element: dq 3
array4element: dq 9
array5element: dq 2
arrayElementsCount: dq 5

section .bss
dataArray: resb 4  + 20; 4byte counter +  5 * 4 bytes data
