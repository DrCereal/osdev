#include <asm/io.h>
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

void updateCursor()
{
	char high = terminal_pos >> 8;
	char low = terminal_pos & 0x0f;
	outb(0x03d4, 0x0f);
	outb(0x03d5, low);
	outb(0x03d4, 0x0e);
	outb(0x03d5, high);
}

void putchar(char c)
{
	VIDMEM[terminal_pos] = make_vga_entry(c, terminal_color);

	terminal_pos++;
	if(terminal_pos >= 80 * 25)
	{
		terminal_pos = 0;
	}
	updateCursor();
}

void putchar_color(char c, char color)
{	
	VIDMEM[terminal_pos] = make_vga_entry(c, color);

	terminal_pos++;
	if(terminal_pos >= 80 * 25)
	{
		terminal_pos = 0;
	}
	updateCursor();
}

void putint(unsigned int i)
{
	char digits[10];
	unsigned char count = 0;
	
	do
	{
		digits[count] = i % 10;
		i = i / 10;
		count++;
	}while(i != 0);

	while(count > 0)
	{
		putchar(digits[count - 1] + 0x30);
		count--;
	}
}

void puthex(unsigned int i)
{
	putchar('0');
	putchar('x');
	char digits[8];
	unsigned char count = 0;
	
	do
	{
		digits[count] = i % 0x10;
		i = i / 0x10;
		count++;
	}while(i != 0);

	while(count > 0)
	{
		if(digits[count - 1] > 9)
			putchar(digits[count - 1] + 0x36);
		else
			putchar(digits[count - 1] + 0x30);
		count--;
	}
}

void print(char* string)
{
	for(int i = 0; string[i] != 0; i++)
	{
		putchar(string[i]);
	}
}
