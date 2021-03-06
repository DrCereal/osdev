#include <irq.h>
#include <traps.h>
#include <asm/io.h>

extern struct idt_entry idt[256];

extern void timer();
extern void keyboard();
extern void fd_interrupt();

void set_interrupt_gate(unsigned short i, unsigned int ir)
{
	idt[i].offset_low = ir & 0xffff;
	idt[i].offset_high = ir >> 16;

	idt[i].selector = 0x8;

	idt[i].flags = 0x8e;

	idt[i].zeros = 0x0;
}

void remap_pic()
{
	outb(0x20, 0x11);
	outb(0x21, 0x20);
	outb(0xa1, 0x28);
	outb(0x21, 0x04);
	outb(0xa1, 0x02);
	outb(0x21, 0x01);
	outb(0xa1, 0x01);

	outb(0x21, 0x00);
	outb(0x21, 0x00);
}

void irq_init()
{
	remap_pic();
	//FDC interrupt is not masked in the PIC
	outb(0x21, 0xbc);
	
	set_interrupt_gate(32, (unsigned int)&timer);
	set_interrupt_gate(33, (unsigned int)&keyboard);

	//IRQ 6 is now set up to 'fd_interrupt()' located in assembly.asm
	set_interrupt_gate(38, (unsigned int)&fd_interrupt);
	//proof:
	//__asm__("int $38");
	//for(;;);
}
