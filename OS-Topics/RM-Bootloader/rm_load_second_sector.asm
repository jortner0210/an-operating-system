;
; Read sectors into memory.
;
; Int 13/ah = 02h
;   - ah = 02h
;   - al = number of sectors to read.
;   - ch = low eight bits of cylinder number.
;   - cl = sector number 1-63 (bit 0-5).
;   - dh = head number
;   - dl = drive number (bit 7 seet for hard disk).
;   - es:bx -> data buffer
;
; Return:
;   - cf = set on error
;   - ah = status
;   - al = number of sectors transferred
;

;
; Set label to load data to: Register bx
;
rm_load_second_sector:
    mov ah, 0x2 ; Read sector command
    mov al, 0x1 ; Read one sector
    mov ch, 0x0 ; Cylinder low eight bits
    mov cl, 0x2 ; Read sector two
    mov dh, 0x0 ; Head number
    
    int 0x13
    jc .error
    ret


.error:
    mov si, LOAD_SECTOR_ERROR_MESSAGE
    call rm_print_string
    jmp $


LOAD_SECTOR_ERROR_MESSAGE: db "Error Reading from disk!"