#ifndef STRING
#define STRING

//GG, this took ages to do.
inline int strlen(char* str)
{
	int i = 0;
	__asm__ volatile(
		"cld\n"
		"1: lodsb\n"
		"cmpb $0, %%al\n"
		"je 2f\n"
		"incl %0\n"
		"jmp 1b\n"
		"2:\n":
		"=c"(i):
		"S"(str)
	);
	return(i);
}

char strcmp(char* str1, char* str2)
{
	int str1_len = strlen(str1);
	if(str1_len != strlen(str2))
		return(0);

	char ret = 0;

	__asm__(
		"cld\n"
		"repe cmpsb\n"
		"jcxnz 1f\n"
		"jmp 2f\n"
		"1: movb $1, %0\n"
		"2:\n":
		"=d"(ret):
		"c"(str1_len),
		"S"(str1),
		"D"(str2)
	);
	return(ret);
}

void memset(char* str, char value, int num)
{
	__asm__ volatile(
		"cld\n"
		"rep stosb\n": :
		"c"(num),
		"a"(value),
		"D"(str)
	);
}

#endif
