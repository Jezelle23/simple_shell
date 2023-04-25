#include "customshell.h"

/**
 * copyString - copies string
 * @deststr: location to place copy
 * @srcstr: where to copy from
 * Return: pointer to dest
 */
char *copyString(char *deststr, char *srcstr)
{
	int i = 0;

	if (deststr == srcstr || srcstr == 0)
		return (deststr);
	while (srcstr[i])
	{
		deststr[i] = srcstr[i];
		i++;
	}
	deststr[i] = 0;
	return (deststr);
}

/**
 * duplicateString - clones a string
 * @strdup: input string
 * Return: pointer to dup'd string
 */
char *duplicateString(const char *strdup)
{
	int len = 0;
	char *res;

	if (strdup == NULL)
		return (NULL);
	while (*strdup++)
		len++;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	for (len++; len--;)
		res[len] = *--strdup;
	return (res);
}

/**
 * printString - prints string
 * @pstr: string input
 * Return: void
 */
void printString(char *pstr)
{
	int x = 0;

	if (!pstr)
		return;
	while (pstr[x] != '\0')
	{
		_putchar(pstr[x]);
		x++;
	}
}

