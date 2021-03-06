#ifndef TERMINAL
#define TERMINAL

enum vga_color
{
	COLOR_BLACK,
	COLOR_BLUE,
	COLOR_GREEN,
	COLOR_CYAN,
	COLOR_RED,
	COLOR_MAGENTA,
	COLOR_BROWN,
	COLOR_LIGHT_GREY,
	COLOR_DARK_GREAY,
	COLOR_LIGHT_BLUE,
	COLOR_LIGHT_GREEN,
	COLOR_LIGHT_CYAN,
	COLOR_LIGHT_RED,
	COLOR_LIGHT_MAGENTA,
	COLOR_LIGHT_BROWN,
	COLOR_WHITE,
};

unsigned char make_VGA_color(enum vga_color fg, enum vga_color bg);

void terminal_set_color(unsigned char color);
void terminal_clear();
void terminal_init();

void set_cursor(unsigned short nposition);
unsigned short get_cursor();
void set_char(unsigned char c);

void putChar(unsigned char c);
void putChar_color(unsigned char c, unsigned char color);
void putInt(unsigned int i);
void putHex(unsigned int i);
void print(char* string);

#endif
