;
; Kernel entry to ensure main is called
;

[bits 32]
[extern main] 

call main     ; Invoke main() in our C kernel

jmp $