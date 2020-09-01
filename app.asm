; initkfs, 2020
; ---------------------
%include "lib/com/com.inc"
%include "lib/bits/bits.inc"
%include "lib/sys/sys.inc"
%include "lib/array/array.inc"
%include "lib/datetime/datetime.inc" 
%include "lib/string/str.inc"
%include "lib/uterm/uterm.inc"
%include "lib/drawing/drawing.inc"
%include "lib/debug/debug.inc"

section .data
nextRandomSeed: dq 1

catContentStart: incbin "data/cat.txt"
catContentSize: equ $-catContentStart

appVersion: db "0.1a", 10, 0

textLineSeparator: db `\n`

cliDebugArg: db "-d", 0
cliHelpArg: db "-h", 0
cliVersionArg: db "-v", 0
cliPrintAllMessagesArg: db "-a", 0

; Info messages
infoMessagePrintUsage: db `Usage:\n -a Print all philosophical messages \n -d Print debug information \n -v Print version\n`, 0
infoReturnCode: db "Return code: %d", 10, 0

; Error messages
errorMessageCliArgsInvalid: db "Invalid command line parameters", 10, 0

; Domain messages, see https://en.wikipedia.org/wiki/AFI's_100_Years...100_Movie_Quotes
message1: db "May the Force be with you!", 0
; use ASCII encoding, https://en.wikipedia.org/wiki/Apostrophe
message2: db "Fasten your seatbelts. It's going to be a bumpy night", 0
message3: db "I love the smell of napalm in the morning!", 0
message4: db "The stuff that dreams are made of", 0
message5: db "There's no place like home", 0
message6: db "Why don't you come up sometime and see me?", 0

section .bss
messagesArray: resq 6

section .text

global main

main:

	xor r8, r8	; reset bit flags for program logic
	movzx r15, byte [rel textLineSeparator] ; save line separator
	mov	rax, rdi
	; first cli argument is the name of the binary file
	cmp rax, 2
	jg errInvalidCli
	cmp rax, 1
	je initOutputMessages	; no arguments found

	mov rdi, [rsi + 8]  ; first argument address with built-in С-runtime

.checkCliPrintHelp:
	mov rsi, cliHelpArg
	call str_cmp
	je printUsage

.checkCliPrintVersion:
	mov rsi, cliVersionArg
	call str_cmp
	je printVersion

.checkCliPrintAllMessages:
	mov rsi, cliPrintAllMessagesArg
	call str_cmp
	jne .checkCliPrintDebug

	bts r8, 0
    jmp initOutputMessages

.checkCliPrintDebug:
	mov rsi, cliDebugArg
	call str_cmp
	; cli args not empty, but no match was found
	jne errInvalidCli

	bts r8, 1

initOutputMessages:
	mov rdi, messagesArray
	mov rsi, 8	; array element size
	call array_init

	xor rsi, rsi
	mov rax, message1
	call addMessageNewIndexUnsafe
	mov rax, message2
	call addMessageNewIndexUnsafe
	mov rax, message3
	call addMessageNewIndexUnsafe
	mov rax, message4
	call addMessageNewIndexUnsafe
	mov rax, message5
	call addMessageNewIndexUnsafe
	mov rax, message6
	call addMessageNewIndexUnsafe

	bt r8, 0
	jc printAllMessages

setTerminalSettings:
	mov rdi, '1;32' ; light green color
	call uterm_format

calculateIndentForPrintImage:

.calculateImageWidthByFirstLine:
	mov rdi, catContentStart
	xor rcx, rcx
	dec rcx
	mov rax, r15
	repne scasb
	neg rcx
	test rcx, rcx
	jle printUnmodifiedCat

.calculateImageIndent:
	call uterm_width
	cmp rax, rcx
	jle printUnmodifiedCat

	sub rax, rcx

	test rax, rax
	jle printUnmodifiedCat

	mov rsi, 2 ; calculate borders
	xor rdx, rdx
	idiv rsi

	mov r14, rax ; save indent to register

printCatWithIndent:
	mov rcx, catContentSize
	mov rsi, catContentStart
	xor r9, r9
	inc r9
.printCatChars: 

.checkIsPrintLeftIndent:
	test r9, r9
	je .checkCharIsLineBreak

.printLeftIndent:
	xor r9, r9
	mov r10, r14
.loopIndent:
	mov rdi, ' '
	call sys_writeb
	test rdx, rdx
	jne systemExit
	dec r10
	test r10, r10
	je .checkCharIsLineBreak
	jmp .loopIndent

.checkCharIsLineBreak:
 	lodsb
	cmp al, r15b
	jne .printCatChar

.setIndentNeed:
	xor r9, r9
	inc r9

.printCatChar: 	 
	mov rdi, rax
	call sys_writeb

 	loop .printCatChars
	
	jmp printRandomMessage

printUnmodifiedCat:
    mov rdi, catContentStart
	mov rsi, catContentSize
	call sys_write

printRandomMessage:

	mov rdi, messagesArray
	call array_count
	test rdx, rdx
	jne systemExit

	mov rsi, rax

.calculateRandomMessage:
	; init random generator
	call dt_timestamp
	test rdx, rdx
	jne systemExit
	mov [rel nextRandomSeed], rax

	call rand
	test rdx, rdx
	jne systemExit
	
	mov rdi, rax
	call calculateMessageIndex
	test rdx, rdx
	jne systemExit

	mov rdi, messagesArray
	mov rsi, rax
	call array_get
	test rdx, rdx
	jne systemExit

.printMessage:
	mov rdi, rax
	xor rsi, rsi
	inc rsi
	xor rdx, rdx
	inc rdx
	call draw_box_message

	call uterm_format_end

	bt r8, 1
	jc printDebugInfo

	jmp systemExit

rand:
	push rbx

    mov rax, [rel nextRandomSeed]
    mov rbx, 1103515245
    mul rbx
    add rax, 12345
    mov [rel nextRandomSeed], rax
    mov rbx, 32768
    xor rdx, rdx
    div ebx
	xor rdx, rdx

	pop rbx
	ret

calculateMessageIndex:
	push rcx
	; rdi - random number
	; rsi - message count
	xor rdx, rdx
	mov rax, rdi
	mov rcx, rsi
	idiv rcx
	mov rax, rdx
	xor rdx, rdx
	pop rcx
	ret

addMessageNewIndexUnsafe:
	; rax - new message
	; rsi - index
	mov rdx, rax
	call array_set
	test rdx, rdx
	jne systemExit

	inc rsi ; increment index, if the index exceeds size of the array, then the array_set will return an error

	ret

printAllMessages:
	mov rdi, messagesArray
	call array_count
	test rdx, rdx
	jne systemExit

	test rax, rax
	jle systemExit

	mov rbx, rax
	xor rcx, rcx
.loopPrintMessage:
	mov rdi, messagesArray
	mov rsi, rcx
	call array_get
	test rdx, rdx
	jne systemExit

	mov rdi, rax
	xor rsi, rsi
	call sys_writestr
	test rdx, rdx
	jne systemExit

	call sys_writeln

	inc rcx

	cmp rcx, rbx
	jne .loopPrintMessage
	jmp systemExit

printUsage:
	mov rdi, infoMessagePrintUsage
	xor rsi, rsi
	call sys_writestr
	jmp systemExit

printVersion: 
	mov rdi, appVersion
	xor rsi, rsi
	call sys_writestr
	jmp systemExit

printDebugInfo:
	call debug_print_regd
	mov rdi, infoReturnCode
	mov rsi, rdx
	call str_printf
	jmp systemExit

errInvalidCli:
	mov rdi, errorMessageCliArgsInvalid
	xor rsi, rsi
	call sys_writestr
	test rdx, rdx
	jne systemExit
	jmp printUsage

systemExit:
	mov rdi, rdx
    call sys_exit
