//This will probably be changed in the future!

#include <asm/io.h>
#include <terminal.h>
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
	terminal_init();

	while(1)
	{
		print("The scancode was: ");
		char tmpStr[2] = {0, 0};
		tmpStr[0] = kbrd_get_key();
		print(tmpStr);
		print(", ");
		putHex(tmpStr[0]);
		print("\n");
	}

	for(;;);
}
