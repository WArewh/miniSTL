%include "boot/boot.inc"

section boot vstart=0x7C00
    mov ax, cs
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov fs, ax
    mov sp, 0x7C00
    ; 清屏
    mov ax, 0x0600
    mov bx, 0x0700
    mov cx, 0x0000
    mov dx, 0x184F
    int     0x10
    ; 调整下标位置
    mov ah, 0x02
    mov bx, 0x0000
    mov dx, 0x0000
    int     0x10
    ; 获取下标位置
    mov ah, 0x03
    mov bh, 0x0000
    int     0x10
    ; 打印字符串
    mov ax, bootStartMsg
    mov bp, ax
    mov cx, 0x000B
    mov ax, 0x1301
    mov bx, 0x000F
    int     0x10
    ;读取一个扇区
    mov eax,loaderStartSection
    mov bx, loaderBaseAddr 
    mov cx, 1
    call    read_section
    ; 调整下标位置
    mov ah, 0x02
    mov bx, 0x0000
    mov dx, 0x0100
    int     0x10
    ; 打印字符串
    mov ax, bootEndMsg
    mov bp, ax
    mov cx, 0x0009
    mov ax, 0x1301
    mov bx, 0x000F
    int     0x10

    jmp     loaderBaseAddr

;读扇区
read_section:
    mov esi,eax
    mov di,cx
;   获得读取的扇区个数
    mov dx,0x1F2
    mov al,cl
    out dx,al
    mov eax,esi
;   将地址写入0x1F3~0x1F6
    mov cl,8
    mov dx,0x1F3
    out dx,al

    shr eax,cl
    mov dx,0x1F4
    out dx,al

    shr eax,cl
    mov dx,0x1F5
    out dx,al

    shr eax,cl
    and al,0x0F
    or  al,0xE0
    mov dx,0x1F6
    out dx,al

    mov dx,0x1F7
    mov al,0x20
    out dx,al
; 数据没有准备好
.if_not_ready:
    nop
    in  al,dx
    and al,0x88
    cmp al,0x08
    jnz .if_not_ready
; 每次读两个字节 一个扇区读256次
    mov ax,di
    mov dx,0x0100
    mul dx
    mov cx,ax
    mov dx,0x1F0

.go_on_read:
    in  ax,dx
    mov [bx],ax
    add bx,2
    loop .go_on_read
    ret

    bootStartMsg db  "Boot Start!"
    bootEndMsg   db  "Boot End!"

    times   510-($-$$)  db  0
    db      0x55,0xaa