extern print, ip, fd_irq_handled
extern do_keyboard

global error_divide, timer, keyboard, fd_interrupt
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
	call reset_pic
	iret

keyboard:
	call do_keyboard
	call reset_pic
	iret

;FDC interrupt, this interrupt is not called after FDC reset.
fd_interrupt:
	mov BYTE [fd_irq_handled], 1
	call reset_pic
	iret

;Misc assembly functions

reset_pic:
	push eax
	mov al, 0x20
	out 0x20, al
	pop eax
	ret

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
	jmp $

test_msg db "Just testing the trap! :-)", 10, 0
reserved_msg db "The reserved trap was called!", 10, 0
