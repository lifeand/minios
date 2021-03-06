;
;
;	boot.s --- 内核从这里开始
; 

; Multiboot 魔术,  使用grub 
MBOOT_HEADER_MAGIC	equ	0x1BADB002

; 0 号位表示素有引导模块将按也(4kb) 边界对齐
MBOOT_PAGE_ALIGN	equ	1 << 0 

; 1 号位通过 Multiboot 信息结构的 mem_* 域包括可用内存的信息
; 
MBOOT_MEM_INFO		equ 	1 << 1 

; 
MBOOT_HEADER_FLAGS	equ	MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO 
; 
; 
MBOOT_CHECKSUM		equ	-(MBOOT_HEADER_MAGIC+MBOOT_HEADER_FLAGS)

;
;	0	u32	magic 
;	4	u32	flags
;	8	u32	checksum
;
;

[BITS 32]	; 所有代码以 32-bit 的方式编译
section .text	; 
;

dd MBOOT_HEADER_MAGIC
dd MBOOT_HEADER_FLAGS
dd MBOOT_CHECKSUM 

[GLOBAL start]	; 向外部声明内核代码入口，此处提供该声明给连接器
[GLOBAL glb_mboot_ptr]	; 向外部声明 struct multiboot * 变量
[EXTERN kern_entry]	; 声明内核 C 代码的入口

start:
	cli

	mov esp, STACK_TOP
	mov ebp, 0
	and esp, 0FFFFFFF0H
	mov [glb_mboot_ptr], ebx ;
	call kern_entry
stop:
	hlt	;停机指令，可以降低CPU 功耗
	jmp stop	;

;
section .bss
stack:
	resb 32768
glb_mboot_ptr:		; 全局的 multiboot 结构体指针
	resb 4 

STACK_TOP	equ	$-stack-1 ; 内核栈鼎， $ 当前地址

