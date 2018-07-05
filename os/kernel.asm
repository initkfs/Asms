BITS 16
ORG 0x0000
; initkfs, 2018
; ---------------------
;https://stackoverflow.com/questions/50540401/drawing-pixels-in-vesa-graphic-mode
;http://www.drdobbs.com/programming-with-vesa-bios-extensions/184403213
main:
    mov ax, cs
    mov ds, ax
     
    mov ax, 4f02h ;Set VBE video mode, http://www.columbia.edu/~em36/wpdos/videomodes.txt
    mov bx, 103h ; VBE mode number,  800x600x256, bpp 8
    int 10h
    
    ; AX = Width
	; BX = Height
	; CL = Bits per pixel
	;https://wiki.osdev.org/User:Omarrx024/VESA_Tutorial
    mov [width], ax
    mov [height], bx
    mov [bpp], cl

	;Get video mode info
	mov ax, 4f01h ; Get VESA mode information
	mov cx, 105h ; Input: CX = VESA mode number from the video modes array
	mov di, modeInfo  ;Input: ES:DI = VESA Mode Information Structure.
	int 10h
	cmp ax, 0x004F ; AX = 0x004F on success, other values indicate a BIOS error or a mode-not-supported error.
	jne error
	
	;https://github.com/paulpela/asmlib/blob/master/pure64/pure64.asm
	mov ax, [modeInfo + 8] ;WinASegment == 0xa000,
	mov [VbeModeInfo + VbeModeInfo.segment_a], word ax
	
	mov ax, [VbeModeInfo + VbeModeInfo.segment_a]
	mov es, ax
	
	xor di, di 	
drawTopBorder:
    mov al, 0x0b  ; color, http://www.fountainware.com/EXPL/vga_color_palettes.htm
    mov cx, 10*800
    rep stosb
	
waitKeyboard:
	;Wait for any key press
	xor ax, ax
	int 16h ; bios keyboard interrupt

error:
	;Restore DOS text mode
	mov ax, 0003h
	int 10h

exit:
	mov ax, 4c00h ; bios exit
	int 21h

section .data
;TODO replace
STRUC VbeModeInfo
	.segment_a: resw 1
ENDSTRUC
modeInfo    resb 256
width resw 1
height resw 1
bpp resw 1




















