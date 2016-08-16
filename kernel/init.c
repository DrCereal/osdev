//This will probably be changed in the future!

#include <shell.h>
#include <gdt.h>
#include <traps.h>
#include <irq.h>

extern void sti();

void init()
{
	install_gdt();
	traps_init();
	irq_init();
	sti();

	shell_init();

	for(;;);
}
