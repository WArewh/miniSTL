; ----------------------------------------------------------------
; 	boot.s -- 内核从这里开始
; ----------------------------------------------------------------

MBOOT_HEADER_MAGIC 	equ 	0x1BADB002

MBOOT_PAGE_ALIGN 	equ 	1 << 0 
MBOOT_MEM_INFO 		equ 	1 << 1    
MBOOT_HEADER_FLAGS 	equ 	MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM 		equ 	- (MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

[BITS 32]

section .text

dd MBOOT_HEADER_MAGIC 	
dd MBOOT_HEADER_FLAGS   
dd MBOOT_CHECKSUM       

[GLOBAL start] 		
[GLOBAL glb_mboot_ptr] 	
[EXTERN kern_entry] 	

start:
	cli  			 			; 此时还没有设置好保护模式的中断处理，要关闭中断
	mov esp, STACK_TOP  	 	; 设置内核栈地址
	mov ebp, 0 		 			; 帧指针修改为 0
	and esp, 0FFFFFFF0H	 		; 栈地址按照16字节对齐
	mov [glb_mboot_ptr], ebx 	; 将 ebx 中存储的指针存入全局变量
	call kern_entry		 		; 调用内核入口函数
stop:
	hlt 			 			; 停机指令，什么也不做，可以降低 CPU 功耗
	jmp stop 		 			; 到这里结束，关机什么的后面再说

;-----------------------------------------------------------------------------

section .bss 			 		; 未初始化的数据段从这里开始
stack:
	resb 32*1024 	 	 		; 这里作为内核栈
glb_mboot_ptr: 			 		; 全局的 multiboot 结构体指针
	resb 4

STACK_TOP equ $-stack-1 	 	; 内核栈顶，$ 符指代是当前地址

;-----------------------------------------------------------------------------
