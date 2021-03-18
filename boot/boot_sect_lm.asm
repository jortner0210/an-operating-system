; https://wiki.osdev.org/Setting_Up_Long_Mode
[bits 16]

[org 0x7c00] 
mov [BOOT_DRIVE], dl        ; BIOS stores the boot drive in DL, remember for later

mov bx, REAL_MODE_BOOT_MSG  ; Announce start in 16-bit real mode.
call print_string

call load_all_boot          ; Load all of the bootloaders code, to access later

call detect_cpuid
call detect_long_mode
call setup_paging


mov ecx, 0xC0000080         ; Set the C-register to 0xC0000080, which is the EFER MSR.
rdmsr                       ; Read from the model-specific register.
or eax, 1 << 8              ; Set the LM-bit (bit 8)
wrmsr                       ; Write to the model-specific register
;; Enable paging and protected mode
mov eax, cr0
or eax, 1 << 31 | 1 << 0
mov cr0, eax
;mov bx, COMPAT_MODE_MSG  
;call print_string
;
;lgdt [GDT64.Pointer]         ; Load the 64-bit global descriptor table.
;jmp GDT64.Code:Realm64

jmp boot2

jmp $

load_all_boot:
    mov bx, post_boot_sector    ; Load the full bootloader
    mov dh, 0x2              
    mov dl, [BOOT_DRIVE]    
    call disk_load
    ret

GDT64:                           ; Global Descriptor Table (64-bit).
    .Null: equ $ - GDT64         ; The null descriptor.
    dw 0xFFFF                    ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 0                         ; Access.
    db 1                         ; Granularity.
    db 0                         ; Base (high).
    .Code: equ $ - GDT64         ; The code descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 10011010b                 ; Access (exec/read).
    db 10101111b                 ; Granularity, 64 bits flag, limit19:16.
    db 0                         ; Base (high).
    .Data: equ $ - GDT64         ; The data descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 10010010b                 ; Access (read/write).
    db 00000000b                 ; Granularity.
    db 0                         ; Base (high).
    .Pointer:                    ; The GDT-pointer.
    dw $ - GDT64 - 1             ; Limit.
    dq GDT64                     ; Base.

%include "./boot/modules/disk_load.asm"
%include "./boot/modules/print_string.asm"

BOOT_DRIVE:         db 0
REAL_MODE_BOOT_MSG: db "16-bit Real Mode.", 0x0d, 0
COMPAT_MODE_MSG:    db "Entered Compatibility Mode!", 0x0d, 0
ANOTHER_SECTOR_MSG: db "/--- ANOTHER SECTOR LOADED ---/", 0x0d, 0

;
; Boot Sector Padding and Magic number
;
times 510-($-$$) db 0 ; Padding - program must fit 512 bytes
dw 0xaa55             ; Boot sector magic number

post_boot_sector:

;
; Check if CPUID is supported by attempting to flip the ID bit (21)
; in the FLAGS register. If it can be flipped, CPUID is available.
;
CPUID_DETECTED_MSG: db "CPUID Support Dectected!", 0x0d, 0
NO_CPUID_MSG:       db "CPUID is not supported on this machine!", 0x0d, 0

detect_cpuid:
    pushfd
    pop eax           ; Copy FLAGS to EAX

    mov ecx, eax      ; Copy EAX to ECX for comparison later

    xor eax, 1 << 21  ; Flip the ID bit

    push eax          ; Copy EAX to FLAGS
    popfd       

    pushfd            ; Copy FLAGS back to EAX.
    pop eax           ; Bit will be flipped if CPUID is available.

    push ecx          ; Restore FLAGS from old version stored in ECX
    popfd

    xor eax, ecx      ; Compare EAX and ECX. If they are equal then
                      ; the bit wasn't flipped and CPUID is not supported.
    jz no_cupid

    mov bx, CPUID_DETECTED_MSG  
    call print_string
    ret

no_cupid:
    mov bx, NO_CPUID_MSG  
    call print_string
    jmp $

;
; Detect whether or not long mode can be used.
; Long mode can only be detected using the extended functions of CPUID (> 0x80000000).
; Check if the function that detects long mode is available or not.
;
LONG_MODE_DETECTED_MSG: db "Long Mode Support Dectected!", 0x0d, 0
NO_LONG_MODE_MSG:       db "Long mode is not supported on this machine!", 0x0d, 0

detect_long_mode:
    mov eax, 0x80000000 ; Set the A-register to 0x80000000
    cpuid               ; CPU identification
    cmp eax, 0x80000001 ; Compare the A-register to 0x80000001
    jb no_long_mode     ; If less, there is no long mode

    ; If extended functionality available, then check for long mode.
    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29   ; Test if the LM-bit (bit 29) is set in the D-register.
    jz no_long_mode     ; If it isn't then long mode not supported.

    mov bx, LONG_MODE_DETECTED_MSG  
    call print_string
    ret

no_long_mode:
    mov bx, NO_LONG_MODE_MSG  
    call print_string
    jmp $

;
; Set up paging.
; Long mode uses PAE paging which includes:
;   - Page-Map Level-4 Table (PML4T): forms the root
;   - Page-Directory Pointer Table (PDPT)
;   - Page-Directory Table (PDT)
;   - Page Table (PT)
;
; The way it works:
;   PML4T[0] -> PDPT
;   PDPT[0] -> PDT
;   PDT[0] -> PT
;   PT -> 0x00000000 - 0x00200000 (A physical memory location)
;
; The Tables are located at the following addresses:
;   PML4T - 0x1000
;   PDPT  - 0x2000
;   PDT   - 0x3000
;   PT    - 0x4000
;
PAGE_TABLE_INIT_MSG: db "Page Table Initialized!", 0x0d, 0

setup_paging:
    ; Disable old paging
    mov eax, cr0                                   ; Set the A-register to control register 0.
    and eax, 01111111111111111111111111111111b     ; Clear the PG-bit, which is bit 31.
    mov cr0, eax

    ; First clear all tables
    mov edi, 0x1000     ; Set destination index to 0x1000
    mov cr3, edi        ; Set control register 3 to the destination index
    xor eax, eax        ; Null EAX
    mov ecx, 4096       ; Set C-register to 4096
    rep stosd           ; Clear the memory
    mov edi, cr3        ; Set the destination index to control register 3

    ; Set up tables, make PML4T[0] point to PDT and so on...
    ; Why 3 used? To set the first to bits which indicate that the page
    ;             is present and that its readable and writable.
    mov DWORD [edi], 0x2003 ; Set the uint32_t at the destination index to 0x2003
    add edi, 0x1000         ; Add 0x1000 to the destination index
    mov DWORD [edi], 0x3003 ; Set the uint32_t at the destination index to 0x3003
    add edi, 0x1000         ; Add 0x1000 to the destination index
    mov DWORD [edi], 0x4003 ; Set the uint32_t at the destination index to 0x4003
    add edi, 0x1000         ; Add 0x1000 to the destination index

    ; Identity map the first two megabytes
    mov ebx, 0x00000003
    mov ecx, 512

set_entry:
    mov DWORD [edi], ebx
    add ebx, 0x1000
    add edi, 8
    loop set_entry

    ; Enable PAE-paging by seting PAE-bit in the fourth control register.
    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    ; Announce page table initialized
    mov bx, PAGE_TABLE_INIT_MSG  
    call print_string
    ret

boot2:
    mov bx, ANOTHER_SECTOR_MSG  
    call print_string

    jmp $

[BITS 64]
 
Realm64:
    cli                           ; Clear the interrupt flag.
    mov ax, GDT64.Data            ; Set the A-register to the data descriptor.
    mov ds, ax                    ; Set the data segment to the A-register.
    mov es, ax                    ; Set the extra segment to the A-register.
    mov fs, ax                    ; Set the F-segment to the A-register.
    mov gs, ax                    ; Set the G-segment to the A-register.
    mov ss, ax                    ; Set the stack segment to the A-register.
    mov edi, 0xB8000              ; Set the destination index to 0xB8000.
    mov rax, 0x1F201F201F201F20   ; Set the A-register to 0x1F201F201F201F20.
    mov ecx, 500                  ; Set the C-register to 500.
    rep stosq                     ; Clear the screen.
    hlt   


times 1024 - ($-$$) db 0
