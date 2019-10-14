#include <stdlib.h>
#include "string_operation.h"

int LengthStr(char* s)
{
	int i = 0;
	while(s[i] != 0)
	{
		i++;
	}

	return i;
}

char* Concatene(char *s1, char* s2)
{
	int l1 = LengthStr(s1);
	int l2 = LengthStr(s2);

	char *result = malloc(l1 + l2 + 1);

	for(int i = 0; i < l1; i++)
		result[i] = s1[i];
	for(int i = 0; i < l2; i++)
		result[l1 + i] = s2[i];

	result[l1 + l2] = '\0';

	return result;
}

int LengthInt(int i)
{
	int n = 0;

	if(i == 0)
		return 1;

	while(i != 0)
	{
		n++;
		i /= 10;
	}

	return n;
}

char* Reverse(char *s)
{
	int length = LengthStr(s);

	for(int i = 0; i < length/2; i++)
	{
		char temp = s[i];
		s[i] = s[length - i - 1];
		s[length - i - 1 ] = temp;
	}

	return s;
}

char* Itoa(int n)
{
	int length = LengthInt(n);

	char* s = malloc((length + 1));
	for(int i = 0; i < length; i++)
	{
		s[i] = n%10 + '0';
		n /= 10;
	}
	s[length] = '\0';

	return Reverse(s);
}
