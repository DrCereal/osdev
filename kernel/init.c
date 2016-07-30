//This will probably be changed in the future!

#include <terminal.h>

void init()
{
	char string[] = "Hello!";
	print(string);
	puthex(16);
	puthex(0x10);
	puthex(32);
	puthex(0x20);
}
