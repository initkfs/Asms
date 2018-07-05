bits 16
ORG 0x7c00
; initkfs, 2018
; ---------------------
;https://stackoverflow.com/questions/39534327/bootloader-not-loading-second-sector
;https://stackoverflow.com/questions/19935688/how-to-transfer-the-control-from-my-boot-loader-to-the-application-located-in-ha
;https://habr.com/company/neobit/blog/203706/
;https://en.wikipedia.org/wiki/INT_13H
	xor ax, ax
	mov ds, ax
	
    mov ss, ax
    mov sp, 0x7c00

resetFloppy:
    xor ax,ax
    int 0x13
    jc resetFloppy

    mov ax, 0x07e0
    mov es,ax 
    xor bx,bx

readfloppy:
	;TODO LBA mov ah, 0x42 ; set to lba extended read
	mov ah,0x2        ; 2 = Read floppy
	mov al,0x1        ; Reading one sector
	mov ch,0x0        ; Track(Cylinder) 1
	mov cl,0x2        ; Sector 2
	mov dh,0x0        ; Head 1
    int 0x13
    jc printFloppyError 
    
    jmp 0x07e0:0x0000
    
   
	msgErrorLoadFloppy db 'Floppy load LBA error! ', 0 
	msgErrorLoadOS db 'OS can not be loaded ', 0

printFloppyError:
	mov si, msgErrorLoadFloppy
	call printString
	jmp end

printString:	; mov si, msq
	mov ah, 0Eh	; int 10h 'print char' BIOS function

.parseChar:
	lodsb			; Get character from string
	cmp al, 0
	je .done
	int 10h	
	jmp .parseChar

.done:
	ret
	
;dap:
;db 0x10   ; size of this package
;db 0x0    ; reserved
;dw 0x1   ; number of sectors to load
;dd 0x07e0 ; destination address
;dq 0x1   ; sector index to load

end:
	mov si, msgErrorLoadOS
	call printString

times 510 - ($ - $$) db 0   ; Fill the rest of sector with 0
dw 0xAA55                   ; This is the boot signature
