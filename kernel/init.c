//This will probably be changed in the future!

#include <shell.h>
#include <gdt.h>
#include <traps.h>
#include <irq.h>
#include <fd.h>

//For debugging
#include <terminal.h>

extern void sti();

void init()
{
	//Also debugging
	terminal_init();

	install_gdt();
	traps_init();
	irq_init();
	sti();

	fd_init();

	while(1)
	{
		fd_read_sec(0, 0, 0, 1);
		print("lel: ");
		putHex(*((char*)0x1000));
		putChar(10);
	}

	//Comment out for now
	//shell_init();

	for(;;);
}
