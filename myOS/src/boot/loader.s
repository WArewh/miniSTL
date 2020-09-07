%include "boot/boot.inc"

section loader vstart=LOADER_BASE_ADDR

    jmp loader_start
    ; 构建gdt及其内部的描述符
    GDT_BASE:   dd    0x00000000 
	            dd    0x00000000

    CODE_DESC:  dd    0x0000FFFF 
	            dd    DESC_CODE_HIGH4

    DATA_STACK_DESC:    dd    0x0000FFFF
		                dd    DESC_DATA_HIGH4

    VIDEO_DESC:         dd    0x80000007            ; limit=(0xbffff-0xb8000)/4k=0x7
	                    dd    DESC_VIDEO_HIGH4      ; 此时dpl已改为0
    times       60      dq    0

    GDT_SIZE    equ   $ - GDT_BASE
    GDT_LIMIT   equ   GDT_SIZE - 1

    SELECTOR_CODE equ (0x0001<<3) + TI_GDT + RPL0   ; 相当于(CODE_DESC - GDT_BASE)/8 + TI_GDT + RPL0
    SELECTOR_DATA equ (0x0002<<3) + TI_GDT + RPL0	
    SELECTOR_VIDEO equ (0x0003<<3) + TI_GDT + RPL0	 

   ;以下是定义gdt的指针，前2字节是gdt界限，后4字节是gdt起始地址

    gdt_ptr dw  GDT_LIMIT
	        dd  GDT_BASE

loader_start:
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

    ; 开启保护模式
    ; A20
    in  al, 0x92
    or  al, 0000_0010B
    out 0x92,al
    ; gdt
    lgdt [gdt_ptr]
    ; CR0置1
    mov eax,cr0
    or  eax,0x00000001
    mov cr0,eax

    jmp dword SELECTOR_CODE:protect_mode_start

    loaderStartMsg db  "Loader Start!"

; 保护模式开始
[bits 32]
protect_mode_start:
    mov ax, SELECTOR_DATA
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov esp,LOADER_STACK_TOP
    mov ax, SELECTOR_VIDEO
    mov gs, ax
    call setup_page

    ; 将GDT中的段描述符映射到线性地址0xc000_0000，即内核全局空间
    sgdt [gdt_ptr]   ; 存储到原来gdt的位置
   ; 将gdt描述符中视频段描述符中的段基址+0xc000_0000，即3G
    mov ebx,[gdt_ptr + 2]  
    or dword [ebx + 0x18 + 4], 0xC000_0000 ; 视频段是第3个段描述符,每个描述符是8字节,故0x18。

    ; 将gdt的基址加上0xc000_0000使其成为内核所在的高地址
    add dword [gdt_ptr + 2], 0xC000_0000 ; 全局描述符表寄存器GDTR也用的是线性地址
    add esp,0xC000_0000

    mov eax,PAGE_DIR_TABLE_POS
    mov cr3,eax

    mov eax,cr0
    or  eax,0x8000_0000
    mov cr0,eax

    lgdt [gdt_ptr]

    mov byte [gs:160*3],'V'

    jmp $

    ; 创建页目录及页表
setup_page:
    ; 先清空页目录表所占的内存，由于内存中可能会有大量随机数据
    mov ecx, 4096   ; 1024项*4字节
    mov esi, 0
clear_page_dir:
    mov byte [PAGE_DIR_TABLE_POS + esi], 0
    inc esi
    loop clear_page_dir
    ; 开始创建页目录项
create_pde:
    mov eax, PAGE_DIR_TABLE_POS
    add eax, 0x1000     ; 4KB，此时eax为第一个页表的位置及属性
    mov ebx, eax        

    ; 下面将页目录表第0和第0x300即768项都存为第一个页表的地址
    or eax, PG_US_U | PG_RW_W | PG_P    
    mov [PAGE_DIR_TABLE_POS + 0x0], eax  
    mov [PAGE_DIR_TABLE_POS + 0x300*4], eax

    sub eax, 0x1000     ; 重新指向自定义的页目录基地址
    mov [PAGE_DIR_TABLE_POS + 1023*4], eax ; 使最后一个目录项指向页目录表自己的地址

    mov ecx, 256    ; 1M/4k = 256
    mov esi, 0
    mov edx, PG_US_U | PG_RW_W | PG_P ; 属性为7,US=1,RW=1,P=1
create_pte:
    mov [ebx+esi*4], edx;ebx已赋值为0x10_1000, 即自定义的第一个页表基地址 
    add edx, 4096
    inc esi
    loop create_pte

; 页目录中创建内核的PDE
    mov eax, PAGE_DIR_TABLE_POS
    add eax, 0x2000     ; 此时eax为第二个页表的位置
    or eax, PG_US_U | PG_RW_W | PG_P  ; 页目录项的属性US,RW和P位都为1
    mov ebx, PAGE_DIR_TABLE_POS
    mov ecx, 254        ; 第769~1022的所有目录项数量
    mov esi, 769        

create_kernel_pde:
    mov [ebx+esi*4], eax
    inc esi
    add eax, 0x1000      
    loop create_kernel_pde
    ret