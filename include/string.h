#ifndef STRING
#define STRING

int strlen(char* str)
{
	int i = 0;
	for(;str[i] != 0; i++);
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

#endif
