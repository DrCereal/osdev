//This will probably be changed in the future!

#include <shell.h>
#include <gdt.h>
#include <traps.h>
#include <irq.h>
#include <fd.h>

extern void sti();

unsigned long lCount = 0;
extern volatile unsigned long count;

void init()
{
	install_gdt();
	traps_init();
	irq_init();
	sti();

	fd_init();

	//Comment out for now
	shell_init();

	for(;;);
}
