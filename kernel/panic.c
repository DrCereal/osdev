#include <terminal.h>

void panic(char* c)
{
	print("\nkernel panic: ");
	print(c);
	for(;;){}
}
