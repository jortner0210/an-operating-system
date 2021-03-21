;
; Switch to 32-bit protected mode
;

[bits 16]

switch_to_pm:
    cli                   ; Switch off interrupts until protected 
                          ; mode interrupt vector is set up.

    lgdt [gdt_descriptor] ; Load global descriptor table.
                          ; defines the protected mode segments for code and data.

    mov eax, cr0          ; To make the switch to protected mode, set
    or eax, 0x1           ; the first bit of CRO, a control register.
    mov cr0, eax          ; Must be set indirectly.

    jmp CODE_SEG:init_pm  ; Make a far jump (i.e to a new segment) to 32-bit code. 
                          ; This forces the CPU to flush its cache and pre-fetched/real-mode instructions

[bits 32]
; Initialize registers and the stack once in PM

init_pm:
    mov ax, DATA_SEG ; Now in PM, old segments are meaningless    
    mov ds, ax       ; so point segment registers to the data
    mov ss, ax       ; selector defined in GDT
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000 ; Update the stack position so it is right at the top
    mov esp, ebp     ; of the free space

    call BEGIN_PM    ; Finally, call some well-know label

