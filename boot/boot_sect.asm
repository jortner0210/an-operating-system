;
; A boot sector that boots a C kernel in 32-bit protected mode.
;
; Source: https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf
;

[org 0x7c00]             ; Tell the assembler where this code will be loaded
KERNEL_OFFSET equ 0x1000 ; This is the memory offset where kernel is loaded

mov [BOOT_DRIVE], dl     ; BIOS stores the boot drive in DL, remember for later

mov bp, 0x9000           ; Set-up the Stack
mov sp, bp

mov bx, MSG_REAL_MODE    ; Announce start in 16-bit real mode.
call print_string

call load_kernel         ; Load the kernel

call switch_to_pm        ; THE POINT OF NO RETURN

jmp $ 

; Include useful routines
%include "./boot/modules/print_string.asm"
%include "./boot/modules/disk_load.asm"
%include "./boot/modules/init_gdt.asm"
%include "./boot/modules/print_string_pm.asm"
%include "./boot/modules/switch_to_pm.asm"

[bits 16]

; Load Kernel routine
load_kernel:
    mov bx, MSG_LOAD_KERNEL ; Print message to announce kernel load
    call print_string
    
    mov bx, KERNEL_OFFSET   ; Set-up parameters for disk_load routine,
    mov dh, 15              ; load the first 15 sectors (excluding the boot
    mov dl, [BOOT_DRIVE]    ; sector) from the boot disk (i.e.) kernel code to 
    call disk_load          ; address KERNEL_OFFSET

    ret

; Beginning of protected mode
[bits 32]

BEGIN_PM:
    mov bx, MSG_PROT_MODE ; Use 32-bit print routine to announce protected mode
    call print_string_pm    

    call KERNEL_OFFSET    ; Now jump to the address of loaded kernel code  

    jmp $

;
; Global Variables
;
BOOT_DRIVE:      db 0
MSG_REAL_MODE:   db "Started in 16-bit Real Mode", 0
MSG_PROT_MODE:   db "Successfully landed in 32-bit Protected Mode", 0
MSG_LOAD_KERNEL: db "Loading kernel into memory", 0

;
; Boot Sector Padding and Magic number
;
times 510-($-$$) db 0 ; Padding - program must fit 512 bytes
dw 0xaa55             ; Boot sector magic number
