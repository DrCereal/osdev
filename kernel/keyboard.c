#include <keyboard.h>
#include <terminal.h>

#include <asm/io.h>

//TODO: Make a proper driver!

//TODO: Add all the f* keys and keypad/extended keys!
unsigned char scan_set[] = {"\x0""\x1b""1234567890-=""\x8"
			"\x9""qwertyuiop[]""\x10"
			"\x0""asdfghjkl;'"
			"`""\x0""\\"
			"zxcvbnm,./""\x0"
			"*""\x0"" ""\x0"};
unsigned char shift_scan_set[] = {"\x0""\x1b""!@#$%^&*()_+""\x8"
			"\x9""QWERTYUIOP{}""\x10"
			"\x0""ASDFGHJKL:\""
			"~""\x0""|"
			"ZXCVBNM<>?""\x0"
			"*""\x0"" ""\x0"};

static volatile unsigned char char_buf;

static unsigned char shift;
static unsigned char control;
static unsigned char alt;
static unsigned char caps;

unsigned char kbrd_get_key()
{
	char_buf = 0;
	while(!char_buf);
	
	return char_buf;
}

void do_keyboard()
{
	unsigned char scan_code = inb(0x60);

	//SHIFT
	if(scan_code == 0x2a || scan_code == 0x36)
	{
		shift = 1;
		return;
	}else if(scan_code == 0xaa || scan_code == 0xb6)
	{
		shift = 0;
		return;
	}

	//CONTROL
	if(scan_code == 0x1d)
	{
		control = 1;
		return;
	}else if(scan_code == 0x9d)
	{
		control = 0;
		return;
	}

	//ALT
	if(scan_code == 0x38)
	{
		alt = 1;
		return;
	}else if(scan_code == 0xB8)
	{
		alt = 0;
		return;
	}

	//CAPS
	if(scan_code == 0x3a)
	{
		//TODO: Make a proper caps!
		//caps = !caps;
	}

	if(scan_code < sizeof(scan_set))
	{
		if(shift || caps)
		{
			char_buf = shift_scan_set[scan_code];
			return;		
		}
		char_buf = scan_set[scan_code];
	}
}
