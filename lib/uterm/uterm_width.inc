; errno=1500
;----------------------------------------------
; initkfs, 2019
; procedure "uterm_width"
; Gets the width of the terminal in columns
;
; Returns: RAX - terminal columns, in characters
;
; Calls: syscall (sys_ioctl)
; Error: if an error occurred while calling the sys_ioctl
;----------------------------------------------
global uterm_width

;http://www.delorie.com/djgpp/doc/libc/libc_495.html
;struct winsize
;{
; unsigned short ws_row;	/* rows, in characters */
; unsigned short ws_col;	/* columns, in characters */
; unsigned short ws_xpixel;	/* horizontal size, pixels */
; unsigned short ws_ypixel;	/* vertical size, pixels */
;};

uterm_width:

	push rdi
	push rsi

	enter 8, 0

	mov rax, 16                 ; kernel function sys_ioctl
    mov rdi, 1                  ; stdout
    mov rsi, 0x5413             ; TIOCGWINSZ
    lea rdx, [rbp - 8]          ; struct winsize address
    syscall
    cmp rax, -1
    je .errSyscalIoctlError
    
    xor rdx, rdx
    movzx rax, word [rbp - 6]	; unsigned short ws_col, columns, in characters
    
    jmp .end
    
.errSyscalIoctlError:
	mov rdx, 1501
	
.end:
	leave
	pop rsi
	pop rdi
	ret
;----------------------------------------------
;			procedure "uterm_width" end
;----------------------------------------------


