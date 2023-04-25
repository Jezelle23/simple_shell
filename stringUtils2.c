#include "customshell.h"

/**
 * _putchar - writes char to std out
 * @c: input char for printing
 * Return: success = 1, errornum otherwise
 */
int _putchar(char c)
{
	static int x;
	static char buff[OUTPUT_BUFF];

	if (c == BUFF_SHELL || x >= OUTPUT_BUFF)
	{
		write(1, buff, x);
		x = 0;
	}
	if (c != BUFF_SHELL)
		buff[x++] = c;
	return (1);
}

/**
 *alphaCheck - looks for alphabets
 *@chr: input character to check for
 *Return: 1 if alpha, else 0
 */
int alphaCheck(int chr)
{
	if ((chr >= 'a' && chr <= 'z') || (chr >= 'A' && chr <= 'Z'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * shell_delim - looks for delimiter in string
 * @checkChar: delimiting char
 * @delimString: string to check for delimiter
 * Return: 1 if true, 0 if false
 */
int shell_delim(char checkChar, char *delimString)
{
	while (*delimString)
	{
		if (*delimString++ == checkChar)
		{
			return (1);
		}
	}
	return (0);
}

/**
 *str2int - converts a string number to int datatype
 *@s: string to process
 *Return: 0 if string has no numbs, else number as int
 */

int str2int(char *s)
{
	int n, i = 1;
	int chk = 0;
	int disp;
	unsigned int res = 0;

	for (n = 0;  s[n] != '\0' && chk != 2; n++)
	{
		if (s[n] == '-')
		{
			i *= -1;
			if (s[n] >= '0' && s[n] <= '9')
			{
				chk = 1;
				res *= 10;
				res += (s[n] - '0');
			}
			else if (chk == 1)
			{
				chk = 2;
			}
		}

		if (i == -1)
		{
			disp = -res;
		}
		else
		{
			disp = res;
		}
	}
	return (disp);
}

/**
 * shelli - checks if its interactive mode
 * @interstruct: info structure
 * Return: 1 when in right mode, else 0
 */

int shelli(info_t *interstruct)
{
	return (isatty(STDIN_FILENO) && interstruct->readfd <= 2);
}

