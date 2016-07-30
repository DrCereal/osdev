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

short terminal_pos;

char make_vga_color(enum vga_color fg, enum vga_color bg);

void terminal_set_color(char color);
void terminal_init();

void putchar(char c);
void putchar_color(char c, char color);
void putint(unsigned int i);
void puthex(unsigned int i);
void print(char* string);

#endif
