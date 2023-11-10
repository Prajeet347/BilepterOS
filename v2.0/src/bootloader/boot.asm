[org 0x7c00]
[bits 16]

%define endl 0x0d, 0x0a

; FAT 12 Header 

jmp short start
nop

bdb_oem:                            db 'MSWIN4.1'
bdb_bytes_per_sector:               dw 512
bdb_sectors_per_cluster:            db 1
bdb_reserved_sectors:               dw 1
bdb_fat_count:                      db 2
bdb_dir_entries_count:              dw 0E0h
bdb_total_sectors:                  dw 2880
bdb_media_descriptor_type:          db 0F0h
bdb_sectors_per_fat:                dw 9
bdb_sectors_per_track:              dw 18
bdb_heads:                          dw 2
bdb_hidden_sectors:                 dd 0
bdb_large_sectors_count:            dd 0

; Extended Boot Record

ebr_drive_number:                   db 0
                                    db 0
ebr_signature:                      db 29h
ebr_volume_id:                      db 12h, 23h, 34h, 45h
ebr_volume_label:                   db 'Bilepter OS'
ebr_system_id:                      db 'FAT12   '


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

    ; Read Something From Disk
    mov [ebr_drive_number], dl
    mov ax, 1
    mov cl, 1
    mov bx, 0x7E00
    call read_disk

    ; Print Message
    mov si, welcomestr
    call puts

    cli
    hlt

floppy_error:
    mov si, readdiskfailed
    call puts
    jmp wait_key_and_reboot

wait_key_and_reboot
    mov ah, 0
    int 16h
    jmp 0FFFFh:0 ; Reboot By Going Back To BIOS Address

.halt:
    cli
    hlt

; Disk Routines

lba_to_chs:
    push ax
    push dx
    
    xor dx, dx
    div word [bdb_sectors_per_track]
    inc dx
    mov cx, dx
    xor dx, dx
    div word [bdb_heads]
    mov dh, dl
    mov ch, al
    shl al, 6
    or ch, al

    pop ax
    mov dl, al
    pop ax

    ret

read_disk:
    push ax
    push bx
    push cx
    push dx
    push di

    push cx
    call lba_to_chs
    pop ax

    mov ah, 02h
    mov di, 3

.retry:
    pusha
    stc
    int 13h
    jnc .done

    popa
    call disk_reset

    dec di
    test di, di
    jnz .retry

.fail:
    jmp floppy_error

.done:
    popa

    pop di
    pop dx
    pop cx
    pop bx
    pop ax
    ret

disk_reset:
    pusha
    mov ah, 0
    stc
    int 13h
    jc floppy_error
    popa
    ret

welcomestr:             db "BilepterOS v1.0 Copyright (C) 2023 Prattay Sarkar", endl, 0
readdiskfailed:         db "[ERROR](DISKPANIC): Failed To Read Disk!", endl, 0

times 510-($-$$) db 0
dw 0xaa55