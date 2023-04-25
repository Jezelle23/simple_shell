#include"customshell.h"
/**
 * cat2str - concatenate two strings
 * @str1: the first string
 * @str2: the second string
 * @numbyte: the number of bytes from the second string to concatenate
 *
 * Return: a pointer to the concatenated string
 */

char *cat2str(char *str1, char *str2, int numbyte)
{
	int name1, name2;
	char *constr = str1;

	name1 = 0;
	name2 = 0;
	while (str1[name1] != '\0')
		name1++;
	while (str2[name2] != '\0' && name2 < numbyte)
	{
		str1[name1] = str2[name2];
		name1++;
		name2++;
	}
	if (name2 < numbyte)
		str1[name1] = '\0';
	return (constr);
}

/**
 * copytext - Copies characters from source string to destination string.
 *            It copies at most numchar characters from source string.
 * @destcopy: Destination string to copy to.
 * @sourcestr: Source string to copy from.
 * @numchar: Maximum number of characters to be copied.
 *
 * Return: A pointer to destination string.
 */

char *copytext(char *destcopy, char *sourcestr, int numchar)
{
	int var1, var2;
	char *concats = destcopy;

	var1 = 0;
	while (sourcestr[var1] != '\0' && var1 < numchar - 1)
	{
		destcopy[var1] = sourcestr[var1];
		var1++;
	}
	if (var1 < numchar)
	{
		var2 = var1;
		while (var2 < numchar)
		{
			destcopy[var2] = '\0';
			var2++;
		}
	}
	return (concats);
}
