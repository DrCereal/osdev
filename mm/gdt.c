#include <gdt.h>

struct gdt_entry gdt[3];
struct gdt_pointer gp;
extern void flush_gdt();

void fill_entry(unsigned char i, unsigned int limit, unsigned int base, unsigned char access, unsigned char flags)
{
	gdt[i].limit_low = limit & 0xffff;
	gdt[i].granularity = (limit >> 16) & 0x0f;

	gdt[i].base_low = base & 0xffff;
	gdt[i].base_middle = (base >> 16) & 0xff;
	gdt[i].base_high = (base >> 24) & 0xff;

	gdt[i].access = access;
	gdt[i].granularity |= flags << 4;
}

void install_gdt()
{
	gp.size = (sizeof(struct gdt_entry) * 3) - 1;
	gp.offset = (unsigned int)&gdt;

	//Null descriptor
	fill_entry(0, 0, 0, 0, 0);

	//Kernel Code descriptor
	fill_entry(1, 0xfffff, 0x0, 0x9a, 0xc);

	//Kernel Data descriptor
	fill_entry(2, 0xfffff, 0x0, 0x92,0xc);

	//TODO: Add user code/data descriptor when there are workable programs! :D

	flush_gdt();
}
