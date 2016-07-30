#include <terminal.h>

static short* VIDMEM = (short*) 0xb8000;

short terminal_pos = 0;
char terminal_color = 0x0f;

char make_vga_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}

short make_vga_entry(char c, char color)
{
	short c16 = c;
	short color16 = color;
	return c16 | color16 << 8;
}

void putchar(char c)
{
	VIDMEM[terminal_pos] = make_vga_entry(c, terminal_color);

	terminal_pos++;
	if(terminal_pos >= 80 * 25)
	{
		terminal_pos = 0;
	}
}

void putchar_color(char c, char color)
{	
	VIDMEM[terminal_pos] = make_vga_entry(c, color);

	terminal_pos++;
	if(terminal_pos >= 80 * 25)
	{
		terminal_pos = 0;
	}
}
