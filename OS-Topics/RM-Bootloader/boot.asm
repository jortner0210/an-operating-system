;
; Simple Real Mode bootloader program that initializes the segments,
; sets a routine to handle interrupt 0x00, triggers the interrupt,
; loads data from sector two and prints the message loaded.
;

[org 0x0] 
[bits 16]
_start:
    jmp short start
    nop

times 33 db 0 ; BIOS parameter block

start:
    jmp 0x7c0:step2

handle_zero:
    mov ah, 0eh
    mov si, INT_ZERO_MESSAGE
    call rm_print_string
    iret

step2:
    ; Initialize segments
    cli            ; Clear interrupts
    mov ax, 0x7c0
    mov ds, ax     ; Set the data segment to 0x7c0
    mov es, ax     ; Set the extra segment to 0x7c0
    mov ax, 0x00
    mov ss, ax     ; Set the stack segment to 0x00
    mov sp, 0x7c00 ; Set the stack pointer to 0x7c00
    sti            ; Enable interrupts

    ;
    ; Interrupt Vector Table
    ;   
    ;   - Each interrupt is described by 4 bytes:
    ;       * The first two bytes are the offset
    ;       * The second two bytes are the segment
    ;
    mov word[ss:0x00], handle_zero  ; Set offset interrupt zero to handle_zero, specifying the stack segment
    mov word[ss:0x02], 0x7c0        ; Set the segment to 0x7c0
    int 0x0

    ; Load data from second sector
    mov bx, buffer
    call rm_load_second_sector

    ; Print message loaded from the second sector
    mov si, buffer
    call rm_print_string

    jmp $

%include "rm_print_string.asm"
%include "rm_load_second_sector.asm"

INT_ZERO_MESSAGE: db "Interrupt 0x0 Triggered!"

times 510 - ($ - $$) db 0
dw 0xaa55

buffer: