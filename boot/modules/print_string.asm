;
; Prints the characters of a null-terminated string 
; to the terminal
;
; reg bx: location of beginning of string
;
print_string:
    pusha
    mov ah, 0x0e ; int 10/ah = 0eh -> scrolling teletype BIOS routine

    loop:
        mov al, [bx]     ; mov current char to al per BIOS teletype routine
        int 0x10         ; call interrupt
        add bx, 1        ; increment current character
        cmp byte [bx], 0 ; check for null
        jne loop         ; return to print_string loop

    popa
    ret


    