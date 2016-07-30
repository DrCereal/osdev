#include <asm/io.h>
#include <terminal.h>

static char* VIDMEM = (char*) 0xb8000;

short terminalPos = 0;
char terminalColor = 0x0f;

char makeVGAColor(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}

void terminalSetColor(char color)
{
	terminalColor = color;
	for(int i = 0; i < 80 * 25; i++)
	{
		VIDMEM[i * 2 + 1] = terminalColor;
	}
}

void terminal_init()
{
	terminalSetColor(makeVGAColor(COLOR_LIGHT_GREY, COLOR_BLACK));
}

void updateCursor()
{
	char high = terminalPos >> 8;
	char low = terminalPos & 0xff;

	outb(0x03d4, 0x0f);
	outb(0x03d5, low);
	outb(0x03d4, 0x0e);
	outb(0x03d5, high);
}

void putChar(char c)
{
	putChar_color(c, terminalColor);
}

void putChar_color(char c, char color)
{
	short absolutePos = terminalPos * 2;
	VIDMEM[absolutePos] = c;
	VIDMEM[absolutePos + 1] = color;

	terminalPos++;
	if(terminalPos >= 80 * 25)
	{
		terminalPos = 0;
	}
	updateCursor();
}

void putInt(unsigned int i)
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
		putChar(digits[count - 1] + 0x30);
		count--;
	}
}

void putHex(unsigned int i)
{
	putChar('0');
	putChar('x');
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
			putChar(digits[count - 1] + 0x36);
		else
			putChar(digits[count - 1] + 0x30);
		count--;
	}
}

void print(char* string)
{
	for(int i = 0; string[i] != 0; i++)
	{
		putChar(string[i]);
	}
}
