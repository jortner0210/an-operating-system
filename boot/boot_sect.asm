;
; Simple boot sector infinite loop
; compile with: nasm boot_sect.asm -f bin -o boot_sect.bin
;
; Source: https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf
; 
; Last section: 4.2
;

[org 0x7c00] ; tells the assembler where this code will be loaded

mov [BOOT_DRIVE], dl

mov bp, 0x8000
mov sp, bp

mov bx, 0x9000
mov dh, 5
mov dl, [BOOT_DRIVE]
call disk_load

mov dx, [0x9000]
call print_hex

mov dx, [0x9000 + 512]
call print_hex

jmp $ ; infinite loop, jump to current address forever

%include "modules/print_string.asm"
%include "modules/print_hex.asm"
%include "modules/disk_load.asm"

;
; Global Variable
;
BOOT_DRIVE: db 0

;
; Padding and Magic number
;
times 510-($-$$) db 0 ; padding - program must fit 512 bytes
dw 0xaa55             ; boot sector magic number

times 256 dw 0xFACE
times 256 dw 0x0000