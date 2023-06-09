#include"customshell.h"
/**
 * convertfunction - convert a long integer to a string in a given base
 * @integer: the integer to convert
 * @num: the base to convert the integer to
 * @raiseA: a flag indicating whether to use uppercase letters for hex values
 *
 * Return: a pointer to the converted string
 */

char *convertfunction(long int integer, int num, int raiseA)
{
	static char *lineofA;
	static char buff[50];
	char symbol = 0;
	char *pointer;
	unsigned long figr = integer;

	if (!(raiseA & CONVERT_FUNCTION) && integer < 0)
	{
		figr = -integer;
		symbol = '-';

	}
	lineofA = raiseA & CONVERT_LOWER ? "0123456789abcdef" : "0123456789ABCDEF";
	pointer = &buff[49];
	*pointer = '\0';

	do	{
		*--pointer = lineofA[figr % num];
		figr /= num;
	} while (figr != 0);

	if (symbol)
		*--pointer = symbol;
	return (pointer);
}

/**
 * decint - prints an integer to a file descriptor
 * @usernum: the integer to print
 * @filed: the file descriptor to write to
 *
 * Return: the number of digits printed
 */

int decint(int usernum, int filed)
{
	int (*displaychar)(char) = _putchar;
	int x, counter = 0;
	unsigned int var, now;

	if (filed == STDERR_FILENO)
		displaychar = displaye;
	if (usernum < 0)
	{
		var = -usernum;
		displaychar('-');
		counter++;
	}
	else
		var = usernum;
	now = var;
	for (x = 1000000000; x > 1; x /= 10)
	{
		if (var / x)
		{
			displaychar('0' + now / x);
			counter++;
		}
		now %= x;
	}
	displaychar('0' + now);
	counter++;

	return (counter);
}

/**
 * convString2int - converts a string to an integer
 * @string2con: the string to convert
 *
 * Return: the converted integer
 */

int convString2int(char *string2con)
{
	int name = 0;
	unsigned long int numins = 0;

	if (*string2con == '+')
		string2con++;
	for (name = 0;  string2con[name] != '\0'; name++)
	{
		if (string2con[name] >= '0' && string2con[name] <= '9')
		{
			numins *= 10;
			numins += (string2con[name] - '0');
			if (numins > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (numins);
}

/**
 * replacetext - replaces a '#' character with a null terminator
 * @address: a pointer to a string
 *
 * This function replaces the first '#' character in the string pointed
 * to by 'address' with a null terminator if it is preceded by a space or
 * if it appears at the beginning of the string.
 */

void replacetext(char *address)
{
	int comm;

	for (comm = 0; address[comm] != '\0'; comm++)
		if (address[comm] == '#' && (!comm || address[comm - 1] == ' '))
		{
			address[comm] = '\0';
			break;
		}
}

/**
 * charaloc - Finds the first occurrence of a character in a string.
 * @parsstr: Pointer to the string to search.
 * @text: The character to search for.
 *
 * Return: A pointer to the first occurrence of the character in the string,
 *         or NULL if the character is not found.
 */

char *charaloc(char *parsstr, char text)
{
	do {
		if (*parsstr == text)
			return (parsstr);
	} while (*parsstr++ != '\0');

	return (NULL);
}
