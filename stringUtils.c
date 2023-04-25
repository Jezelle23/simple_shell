#include "customshell.h"

/**
 * _strlen - gets length of string
 * @str: input string to find length
 * Return: length of string
 */
int _strlen(char *str)
{
	int i = 0;

	if (!str)
		return (0);

	while (*str++)
		i++;
	return (i);
}

/**
 * stringcomp - compares two strings
 * @str1: first string
 * @str2: second string
 * Return: if str1 is less = negative, positive if greater, zero if equal
 */
int stringcomp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * str_Prefix - checks if substring is in string
 * @strsrch: the string we need to search
 * @subssrch: substring we need to find in string
 * Return: location for char in strsrch or NULL
 */
char *str_Prefix(const char *strsrch, const char *subssrch)
{
	while (*subssrch)
		if (*subssrch++ != *strsrch++)
			return (NULL);
	return ((char *)strsrch);
}

/**
 * _strcat - takes to strings and concats
 * @deststr: buffer for dest
 * @srcstr:  buffer for src
 * Return: pointer to dest
 */
char *_strcat(char *deststr, char *srcstr)
{
	char *res = deststr;

	while (*deststr)
		deststr++;
	while (*srcstr)
		*deststr++ = *srcstr++;
	*deststr = *srcstr;
	return (res);
}

