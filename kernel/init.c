//This will probably be changed in the future!

#include <terminal.h>

void init()
{
	char string[] = "Hello!";
	print(string);
	putHex(16);
	putHex(0x10);
	putHex(32);
	putHex(0x20);
}
