#ifndef STRING
#define STRING

//GG, this took ages to do.
inline int strlen(char* str)
{
	int i = 0;
	__asm__ volatile(
		"1:\n"
		"lodsb\n"
		"cmpb $0, %%al\n"
		"je 2f\n"
		"incl %0\n"
		"jmp 1b\n"
		"2:\n":
		"=c"(i):
		"S"(str)
	);
	return i;
}

char strcmp(char* str1, char* str2)
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

void memset(char* str, char value, int bytes)
{
	__asm__("1:\n"
		"movb %1, (%2)"
		"": :
		"c"(bytes),
		"d"(value),
		"D"(str)
	);
}

#endif
