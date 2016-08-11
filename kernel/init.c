//This will probably be changed in the future!

#include <terminal.h>
#include <gdt.h>

void init()
{
	install_gdt();
	terminal_init();
	print("Hello...");
}
