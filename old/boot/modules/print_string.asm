;
; Prints the characters of a null-terminated string to the screen
;
; Register BX: location of beginning of string
;
print_string:
    pusha
    mov ah, 0x0e ; int 10/ah = 0eh -> scrolling teletype BIOS routine

print_string_loop:
    mov al, [bx]          ; Move current char to al per BIOS teletype routine
    int 0x10              ; Call interrupt
    inc bx                ; Increment current character
    cmp byte [bx], 0      ; Check for null
    je print_string_done

    cmp byte [bx], 0x0d   ; Check for new line
    je print_string_new_line
    
    jmp print_string_loop ; Return to print_string loop  

print_string_new_line:
    mov al, 0x0a          ; Print carriage return and line feed.
    int 0x10              ; Then jump back to print string loop.
    mov al, 0x0d
    int 0x10
    jmp print_string_loop

print_string_done:
    popa
    ret


    