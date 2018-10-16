;----------------------------------------------
; initkfs, 2018
;----------------------------------------------

global num_int64_min
num_int64_min:
	mov rax, -9223372036854775808
	xor rdx, rdx
.end:
	ret

global num_int64_max
num_int64_max:
	mov rax, 9223372036854775807
	xor rdx, rdx
.end:
	ret

global num_uint64_max
num_uint64_max:
	mov rax, 18446744073709551615
	xor rdx, rdx
.end:
	ret

global num_int32_min
num_int32_min:
	mov rax, -2147483648
	xor rdx, rdx
.end:
	ret
	
global num_int32_max
num_int32_max:
	mov rax, 2147483647
	xor rdx, rdx
.end:
	ret
	
global num_uint32_max
num_uint32_max:
	mov rax, 4294967295
	xor rdx, rdx
.end:
	ret
	
global num_int16_min
num_int16_min:
	mov rax, -32768
	xor rdx, rdx
.end:
	ret
	
global num_int16_max
num_int16_max:
	mov rax, 32767
	xor rdx, rdx
.end:
	ret
	
global num_uint16_max
num_uint16_max:
	mov rax, 65535
	xor rdx, rdx
.end:
	ret
	
global num_int8_min
num_int8_min:
	mov rax, -128
	xor rdx, rdx
.end:
	ret
	
global num_int8_max
num_int8_max:
	mov rax, 127
	xor rdx, rdx
.end:
	ret
	
global num_uint8_max
num_uint8_max:
	mov rax, 255
	xor rdx, rdx
.end:
	ret
