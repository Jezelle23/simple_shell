#include "customshell.h"

/**
 * pointfree - clears pointer and their values to null
 * @ptr: location of pointer to be cleared
 *
 * Return: 1 when succesfull, else 0.
 */
int pointfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

/**
 **setMemory - sets a memory with a certain byte
 *@s: memory location pointer
 *@b: byte to set memory adress with
 *@n: number of bytes to set
 *Return: pointer to memory location s
 */
char *setMemory(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * freestr - clears strings
 * @pp: string containing strings
 */
void freestr(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * reallocMemory - changes location of a memory block
 * @ptr: pointer to previous mem block
 * @old_size: prev block size
 * @new_size: new block size
 * Return: old block pointer
 */
void *reallocMemory(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
