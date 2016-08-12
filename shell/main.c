#include <shell.h>
#include <keyboard.h>
#include <terminal.h>

#define BUFFER_SIZE 256

static char buffer[BUFFER_SIZE];

static void shell_get_command()
{
	for(int i = 0;;)
	{
		char c = kbrd_get_key();
		switch(c)
		{
			case 8:
				if(i == 0)
					break;

				set_cursor(get_cursor() - 1);
				set_char(' ');
				buffer[--i] = 0;
				break;
			case 10:
				buffer[i] = 0;
				putChar(c);
				return;
			default:
				if(i >= BUFFER_SIZE - 1)
					break;
				putChar(c);
				buffer[i++] = c;
				break;
		}
	}
}

char prompt[] = "# ";

void shell_init()
{
	terminal_init();
	
	while(1)
	{
		print(prompt);
		shell_get_command();
		print(buffer);
		print("\n");
	}
}
