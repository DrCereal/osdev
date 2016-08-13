#include <asm/io.h>
#include <terminal.h>

//TODO: In the future, switch this stuff out for assembly code!

static char* VIDMEM = (char*) 0xb8000;

static unsigned char x = 0;
static unsigned char y = 0;
static unsigned char terminal_color = 0x0;

static void update_cursor();
static void mov_up();

unsigned char make_VGA_color(enum vga_color fg, enum vga_color bg)
{
	return bg << 4 | fg;
}

void terminal_set_color(unsigned char color)
{
	terminal_color = color;
	for(short i = 0; i < 80 * 25; i++)
		VIDMEM[i * 2 + 1] = terminal_color;
}

void terminal_clear()
{
	x = y = 0;
	update_cursor();

	for(short i = 0; i < 80 * 25; i++)
		VIDMEM[i * 2] = ' ';
}

void terminal_init()
{
	terminal_clear();
	terminal_set_color(0x0f);
}

void set_cursor(unsigned short nposition)
{
	x = nposition % 80;
	y = nposition / 80;
	update_cursor();
}

unsigned short get_cursor()
{
	return (y * 80) + x;
}

void set_char(unsigned char c)
{
	unsigned short absolute_pos = ((y * 80) + x) * 2;
	VIDMEM[absolute_pos++] = c;
	VIDMEM[absolute_pos] = terminal_color;
}

static void update_cursor()
{
	if(x >= 80)
	{
		x = 0;
		y++;
	}
	if(y >= 25)
		mov_up();

	unsigned short terminal_pos = (y * 80 + x);

	outb(0x03d4, 0x0f);
	outb(0x03d5, terminal_pos & 0xff);
	outb(0x03d4, 0x0e);
	outb(0x03d5, terminal_pos >> 8);
}

//TODO: Replace with assembly code for better performance!
static void mov_up()
{
	for(int i = 80; i < 25 * 80; i++)
	{
		VIDMEM[(i - 80) * 2] = VIDMEM[i * 2];
		VIDMEM[((i - 80) * 2) + 1] = VIDMEM[(i * 2) + 1];
	}

	for(int i = 80 * 24; i < 80 * 25; i++)
	{
		VIDMEM[i * 2] = ' ';
		VIDMEM[(i * 2) + 1] = terminal_color;
	}

	y = 24;
}

void putChar(unsigned char c)
{
	putChar_color(c, terminal_color);
}

void putChar_color(unsigned char c, unsigned char color)
{
	switch(c)
	{
		case 9:
		{
			char j = x % 8;
			for(char i = 0; i < 8 - j; i++)
				putChar(' ');
			goto skip;
		}
		case 10:
			x = 0;
			y++;
			goto skip;
	}

	short absolute_pos = (y * 80 + x) * 2;
	VIDMEM[absolute_pos] = c;
	VIDMEM[absolute_pos + 1] = color;
	x++;
	
skip:	update_cursor();
}

void putInt(unsigned int i)
{
	unsigned char digits[10];
	unsigned char count = 0;
	
	do
	{
		digits[count++] = i % 10;
		i /= 10;
	}while(i != 0);

	while(count > 0)
		putChar(digits[--count] + 0x30);
}

void putHex(unsigned int i)
{
	putChar('0');
	putChar('x');
	unsigned char digits[8];
	unsigned char count = 0;
	
	do
	{
		digits[count++] = i % 0x10;
		i /= 0x10;
	}while(i != 0);

	while(count > 0)
	{
		if(digits[--count] > 9)
			putChar(digits[count] + 0x37);
		else
			putChar(digits[count] + 0x30);
	}
}

void print(char* string)
{
	for(unsigned long i = 0; string[i] != 0; i++)
		putChar(string[i]);
}
