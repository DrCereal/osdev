extern print, ip
extern do_keyboard

global error_divide, timer, keyboard
global reserved, install_idt, sti

;TODO: Actually make this fix the error!
error_divide:
	push ebp
	mov ebp, esp
	sub esp, 4
	mov DWORD [esp], test_msg
	call print
	add esp, 4
	pop ebp
	iret

;IRQs

timer:
	push eax
	mov al, 0x20
	out 0x20, al
	pop eax
	iret

keyboard:
	call do_keyboard
	push eax
	in al, 0x60
	mov al, 0x20
	out 0x20, al
	pop eax
	iret

;Misc assembly functions

sti:
	sti
	ret

install_idt:
	lidt [ip]
	ret

reserved:
	push ebp
	mov ebp, esp
	sub esp, 4
	mov DWORD [esp], reserved_msg
	call print
	add esp, 4
	pop ebp
	push eax
	mov al, 0x20
	out 0x20, al
	pop eax
	iret

test_msg db "Just testing the trap! :-)", 10, 0
reserved_msg db "The reserved trap was called!", 10, 0
