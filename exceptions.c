#include "customshell.h"


/**
 * displayin - prints a string to a file descriptor
 * @printS: the string to print
 * @writefd: the file descriptor to write to
 *
 * Return: the number of characters printed
 */

int displayin(char *printS, int writefd)
{
	int filede = 0;

	if (!printS)
		return (0);
	while (*printS)
	{
		filede += dispfd(*printS++, writefd);
	}
	return (filede);
}

/**
 * dispfd - writes a character to a file descriptor buffer
 * @textc: the character to be written
 * @filedesc: the file descriptor to write to
 *
 * Return: 1 on success, -1 on failure
 */

int dispfd(char textc, int filedesc)
{
	static int var;
	static char fdbuff[OUTPUT_BUFF];

	if (textc == BUFF_SHELL || var >= OUTPUT_BUFF)
	{
		write(filedesc, fdbuff, var);
		var = 0;
	}
	if (textc != BUFF_SHELL)
		fdbuff[var++] = textc;
	return (1);
}

/**
 * displaye - displays a character string to standard error
 * @str: the character string to be displayed
 *
 * Return: number of characters displayed
 */

int displaye(char str)
{
	static int a;
	static char Ebuff[OUTPUT_BUFF];

	if (str == BUFF_SHELL || a >= OUTPUT_BUFF)
	{
		write(2, Ebuff, a);
		a = 0;
	}
	if (str != BUFF_SHELL)
		Ebuff[a++] = str;
	return (1);
}

/**
 * errorout - Displays an error message on stderr
 * @printedst: Pointer to the error message string
 *
 * Return: None
 */

void errorout(char *printedst)
{
	int instr = 0;

	if (!printedst)
		return;
	while (printedst[instr] != '\0')
	{
		displaye(printedst[instr]);
		instr++;
	}
}

/**
 * display_errmsg - Displays an error message
 * @retinfostruct: A pointer to the info_t struct
 * @specerror: The specific error message to display
 *
 * Return: void
 */

void display_errmsg(info_t *retinfostruct, char *specerror)
{
	errorout(retinfostruct->fileword);
	errorout(": ");
	decint(retinfostruct->line_count, STDERR_FILENO);
	errorout(": ");
	errorout(retinfostruct->argv[0]);
	errorout(": ");
	errorout(specerror);
}

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
