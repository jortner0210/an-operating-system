;
; Simple boot sector infinite loop
; compile with: nasm boot_sect.asm -f bin -o boot_sect.bin
;
; Source: https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf
; 
; Last section: 3.6.2
;

[org 0x7c00] ; tells the assembler where this code will be loaded

mov bx, my_string
call print_string

jmp $ ; infinite loop, jump to current address forever

%include "modules/print_string.asm"

my_string:
    db 'Booting OS',0 ; null-terminated string

;
; Padding and Magic number
;

times 510-($-$$) db 0 ; padding - program must fit 512 bytes

dw 0xaa55             ; boot sector magic number