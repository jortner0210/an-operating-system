;
; Simple boot sector infinite loop
; compile with: nasm boot_sect.asm -f bin -o boot_sect.bin
;
; Source: https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf
; 
; Last section: 4.2
;

[org 0x7c00] ; Tells the assembler where this code will be loaded

mov bp, 0x9000 ; Set the Stack
mov sp, bp

mov bx, MSG_REAL_MODE
call print_string

call switch_to_pm   ; Note: THE POINT OF NO RETURN

jmp $ 

%include "modules/print_string.asm"
%include "modules/print_string_pm.asm"
%include "modules/switch_to_pm.asm"
%include "modules/init_gdt.asm"

; This is where we arrive after switching to protected mode
BEGIN_PM:
    mov bx, MSG_PROT_MODE
    call print_string_pm    ; Use 32-bit print routine

    jmp $

;
; Global Variable
;
MSG_REAL_MODE: db "Started in 16-bit Real Mode", 0
MSG_PROT_MODE: db "Successfully landed in 32-bit Protected Mode", 0

;
; Padding and Magic number
;
times 510-($-$$) db 0 ; padding - program must fit 512 bytes
dw 0xaa55             ; boot sector magic number
