#include <shell.h>
#include <keyboard.h>
#include <terminal.h>
#include <string.h>
#include <fd.h>

#define BUFFER_SIZE 256

//TODO: malloc
static char buffer[BUFFER_SIZE];

static void get_command()
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


//TODO: Fix this when malloc is added!
static char argv[16][32] = {};

static void shell_clear_args()
{
	for(int i = 0; i < 16; i++)
	{
		for(int j = 0; j < 32; j++)
			argv[i][j] = 0;
	}
}

static char parse_command()
{
	//TODO: Remove!
	shell_clear_args();

	int j = 0;
	for(int i = 0; buffer[i] != 0; j++)
	{
		if(j >= 16)
			return(-1);

		for(; buffer[i] == ' '; i++);
		if(buffer[i] == 0)
			break;

		int k = i;
		for(; buffer[i] != ' ' && buffer[i] != 0 && i - k < 32; i++)
			argv[j][i - k] = buffer[i];

		if(i - k >= 32)
			return(-1);

		argv[j][i - k] = 0;
	}
	return(j);
}

//TODO: Implement more&better commands!
static char run_command(char argc)
{
	if(argc == 1)
	{
		if(strcmp(argv[0], "clear"))
		{
			terminal_clear();
			return(1);
		}
		if(strcmp(argv[0], "temp"))
		{
			//This command is temporary and serves no purpose.
			fd_read_sec(0, 0, 0, 1, 2);

			char* membuf = (char*)0x1000;
			for(int i = 0; i < 1024;)
			{
				int j = i;
				for(;i - j < 256; i++)
				{
					putHex(membuf[i] & 0xff);
					putChar(' ');
				}
				kbrd_get_key();
			}
			return(1);
		}
	}
	return(0);
}

void shell_init()
{
	terminal_init();
	
	//TODO: Add escape key combo thing here!
	while(1)
	{
		print("# ");
		get_command();
		char argc = parse_command();

		if(argc == -1)
		{
			print("invalid argument lengths!\n");
			continue;
		}

		if(!run_command(argc))
			print("Invalid command!\n");
	}
}
