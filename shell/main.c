#include <shell.h>
#include <keyboard.h>
#include <terminal.h>

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
			return -1;

		for(; buffer[i] == ' '; i++);
		if(buffer[i] == 0)
			break;

		int k = i;
		for(; buffer[i] != ' ' && buffer[i] != 0 && i - k < 32; i++)
			argv[j][i - k] = buffer[i];

		if(i - k >= 32)
			return -1;

		argv[j][i - k] = 0;
	}
	return j;
}

//TODO: Move these string functions to 'string.h'

static int strlen(char* str)
{
	int i = 0;
	for(;str[i] != 0; i++);
	return i;
}

static char strcmp(char* str1, char* str2)
{
	int str1_len = strlen(str1);
	if(str1_len != strlen(str2))
		return 0;

	for(int i = 0; i < str1_len; i++)
	{
		if(str1[i] != str2[i])
			return 0;
	}
	return 1;
}

//TODO: Implement more&better commands!
static char run_command(char argc)
{
	if(argc == 1)
	{
		if(strcmp(argv[0], "clear"))
		{
			terminal_clear();
			return 1;
		}
		if(strcmp(argv[0], "temp"))
		{
			print("This command is basically just filler at the moment :(\n");
			return 1;
		}
	}
	return 0;
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
