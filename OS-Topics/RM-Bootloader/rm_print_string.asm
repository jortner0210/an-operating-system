;
; Real Mode Print String Routine.
;
; Prints the characters of a null terminated string
; to the terminal.
;

;
; Parameter: 
;   1) SI: A pointer to the beginning of a null-terminated string.
;
rm_print_string:
.loop:
    lodsb       ; Loads byte, word, or double word to 
                ; register AL, AX, EAX, and increment SI. 
    cmp al, 0x0 ; Check for null terminating character
    je .done
    call rm_print_char
    jmp .loop
.done:
    ret

rm_print_char:
    ; int 10/ah = 0eh -> scrolling teletype BIOS routine
    mov ah, 0eh
    int 0x10
    ret