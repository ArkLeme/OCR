#include <stdlib.h>
#include "string_operation.h"

/**
 * \file string_operation.c
 * \brief This file contains all the function related to string.
 * I did not use string.h because... I thought it was not allowed, so i just
 * recode some function.
 * \author William.G
 */

/**
 * \fn int LengthStr(char* s)
 * \brief Compute the length of a string, the string msut end with null char.
 *
 * \param s : the string
 *
 * \return the length of the string
 */
int LengthStr(char* s)
{
	int i = 0;
	while(s[i] != 0)
	{
		i++;
	}

	return i;
}

/**
 * \fn char* Concatene(char *s1, char* s2)
 * \brief Concatene 2 string, it return a new one.
 *
 * \param s1 : first string
 * \param s2 : second string
 *
 * \return pointer to the new string
 */
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

/**
 * \fn int LengthInt(int i)
 * \brief Compute the number of decimal in a number.
 *
 * \param i : number
 *
 * \return number of decimal
 */
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

/**
 * \fn char* Reverse(char *s)
 * \brief Reverse a string.
 *
 * \param s : the string
 *
 * \return the same string
 */
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

/**
 * \fn char* Itoa(int n)
 * \brief Convert an int to a string
 *
 * \param n : the number
 *
 * \return the string
 */
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

/**
 * \fn char* empty_string()
 * \brief Return an empty string
 *
 * \return empty string
 */
char* empty_string()
{
    char *c = malloc(sizeof(char) * 1);
    *c = 0;
    return c;
}
