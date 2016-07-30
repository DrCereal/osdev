#ifndef ASMIO
#define ASMIO

//You have no idea how long this actually took to learn and code.

inline void outb(short port, char val)
{
	__asm__ volatile("outb %0, %1": :
		"a"(val),
		"Nd"(port)
	);
}

inline char inb(short port)
{
	char ret;
	__asm__("inb %1, %0":
		"=a"(ret):
		"Nd"(port)
	);
	return ret;
}

#endif
