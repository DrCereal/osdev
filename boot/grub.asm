[bits 32]

;GRUB INFO. RIP custom bootloader.

MBALIGN	equ 1<<0
MEMINFO	equ 1<<1
FLAGS	equ MBALIGN | MEMINFO
MAGIC	equ 0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

section .bss
align 4
stack_bottom:
resb 16384
stack_top:

section .text
global _start:function (_start.end - _start)

_start:
	mov esp, stack_top
	extern init
	call init
.end:
;Lel, I accidently moved this and got some nice triple faults Xd
die:	cli
	hlt
	jmp die

global flush_gdt
extern gp
flush_gdt:
	lgdt [gp]
	mov ax, 0x10
	mov es, ax
	mov ds, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x8:gdt_ret
gdt_ret:
	ret
