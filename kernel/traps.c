#include <traps.h>

struct idt_entry idt[256];
struct idt_pointer ip;

extern void reserved();
extern void install_idt();

extern void error_divide();

void set_trap_gate(unsigned short i, unsigned int ir)
{
	idt[i].offset_low = ir & 0xffff;
	idt[i].offset_high = ir >> 16;

	idt[i].selector = 0x8;

	idt[i].flags = 0x8f;

	idt[i].zeros = 0x0;
}

void traps_init()
{
	int i = 0;
	ip.size = (sizeof(struct idt_entry) * 256) - 1;
	ip.offset = (unsigned int)&idt;

	set_trap_gate(i++, (unsigned int)&error_divide);

	for(; i < 256; i++)
		set_trap_gate(i, (unsigned int)&reserved);

	install_idt();
}
