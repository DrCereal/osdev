#include <asm/io.h>
#include <terminal.h>

static char* VIDMEM = (char*) 0xb8000;

short terminal_pos = 0;
char terminal_color = 0x0f;

char make_vga_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}

void terminal_set_color(char color)
{
	terminal_color = color;
	for(int i = 0; i < 80 * 25; i++)
	{
		VIDMEM[i * 2 + 1] = terminal_color;
	}
}

void terminal_init()
{
	terminal_set_color(make_vga_color(COLOR_LIGHT_GREY, COLOR_BLACK));
}

void updateCursor()
{
	char high = terminal_pos >> 8;
	char low = terminal_pos & 0xff;

	outb(0x03d4, 0x0f);
	outb(0x03d5, low);
	outb(0x03d4, 0x0e);
	outb(0x03d5, high);
}

void putchar(char c)
{
	putchar_color(c, terminal_color);
}

void putchar_color(char c, char color)
{
	short absolute_pos = terminal_pos * 2;
	VIDMEM[absolute_pos] = c;
	VIDMEM[absolute_pos + 1] = color;

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
