;
; Prints the characters of hexadecimal number
;
; reg dx: number to print
;
print_hex:
    pusha


    popa
    ret

HEX_OUT: db '0x0000',0