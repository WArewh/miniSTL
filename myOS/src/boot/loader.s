%include "boot/boot.inc"

section loader vstart=loaderBaseAddr
    ; 调整下标位置
    mov ah, 0x02
    mov bx, 0x0000
    mov dx, 0x0200
    int     0x10
    ; 打印字符串
    mov ax, loaderStartMsg
    mov bp, ax
    mov cx, 0x000D
    mov ax, 0x1301
    mov bx, 0x000F
    int     0x10

    jmp     $

loaderStartMsg db  "Loader Start!"
