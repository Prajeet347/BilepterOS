[org 0x7c00]
[bits 16]

%define endl 0x0d, 0x0a

start:
    jmp main

puts: ; Function For Printing A String
    push si
    push ax
.loop:
    lodsb
    or al, al
    jz .done
    mov ah, 0x0e
    mov bh, 0
    int 0x10
    jmp .loop
.done:
    pop ax
    pop si
    ret

main:
    ; Setup Data Segments
    mov ax, 0
    mov ds, ax
    mov es, ax

    ; Setup Stack
    mov ss, ax
    mov sp, 0x7c00

    ; Print Message
    mov si, welcomestr
    call puts

    hlt

.halt:
    jmp .halt

welcomestr: db "BilepterOS v1.0 Copyright (C) 2023 Prattay Sarkar", endl, 0

times 510-($-$$) db 0
dw 0xaa55