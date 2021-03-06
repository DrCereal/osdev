#ifndef GDT
#define GDT

struct gdt_entry
{
	unsigned short limit_low;
	unsigned short base_low;
	unsigned char base_middle;
	unsigned char access;
	unsigned char granularity;
	unsigned char base_high;
} __attribute__((packed));

struct gdt_pointer
{
	unsigned short size;
	unsigned int offset;
} __attribute__((packed));

void install_gdt();

#endif
