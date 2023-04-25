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

