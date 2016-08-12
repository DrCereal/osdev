#ifndef TRAPS
#define TRAPS

struct idt_entry
{
	unsigned short offset_low;
	unsigned short selector;
	unsigned char zeros;
	unsigned char flags;
	unsigned short offset_high;
} __attribute__((packed));

struct idt_pointer
{
	unsigned short size;
	unsigned int offset;
} __attribute((packed));

void traps_init();

#endif
