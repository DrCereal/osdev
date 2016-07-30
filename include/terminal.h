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

char make_vga_color(enum vga_color fg, enum vga_color bg);
short make_vga_entry(char c, char color);

void putchar(char c);
void putchar_color(char c, char color);

#endif
