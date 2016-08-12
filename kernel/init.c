//This will probably be changed in the future!

#include <asm/io.h>
#include <terminal.h>
#include <shell.h>
#include <keyboard.h>
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
	//terminal_init();

	shell_init();

	/*while(1)
	{
		print("The scancode was: ");
		char c = kbrd_get_key();
		putChar(c);
		print(", ");
		putHex(c);
		print("\n");
	}*/

	for(;;);
}
