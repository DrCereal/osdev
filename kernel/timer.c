#include <timer.h>
#include <terminal.h>

volatile unsigned long count = 0;

void do_timer()
{
	count++;
}
