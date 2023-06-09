#include"customshell.h"

/**
 * buffchained - Reads a line from standard input.
 * @para: Pointer to a struct containing arguments.
 * @addressb: Address of a pointer to a buffer.
 * @var: Pointer to a variable storing the buffer size.
 *
 * Return: The number of characters read, or -1 upon failure.
 */

ssize_t buffchained(info_t *para, char **addressb, size_t *var)
{
	ssize_t index = 0;
	size_t pointlen = 0;

	if (!*var)
	{
		free(*addressb);
		*addressb = NULL;
		signal(SIGINT, blocksig);
#if CALL_LINE
		index = getline(buf, &pointlen, stdin);
#else
		index = callstr(para, addressb, &pointlen);
#endif
		if (index > 0)
		{
			if ((*addressb)[index - 1] == '\n')
			{
				(*addressb)[index - 1] = '\0';
				index--;
			}
			para->countl = 1;
			replacetext(*addressb);
			histListBuild(para, *addressb, para->historycount++);

			{
				*var = index;
				para->membuff = addressb;
			}
		}
	}
	return (index);
}

/**
 * lineneg - handles negative line numbers
 * @linepara: pointer to struct of arguments
 *
 * Return: the length of the string
 */

ssize_t lineneg(info_t *linepara)
{
	static char *combuff;
	static size_t x, y, z;
	ssize_t a = 0;
	char **c = &(linepara->arg), *b;

	_putchar(BUFF_SHELL);
	a = buffchained(linepara, &combuff, &z);
	if (a == -1)
		return (-1);
	if (z)
	{
		y = x;
		b = combuff + x;

		shouldChain(linepara, combuff, &y, x, z);
		while (y < z)
		{
			if (isMultiDelim(linepara, combuff, &y))
				break;
			y++;
		}

		x = y + 1;
		if (x >= z)
		{
			x = z = 0;
			linepara->commandbuff = CMD_NORM;
		}

		*c = b;
		return (_strlen(b));
	}

	*c = combuff;
	return (a);
}

/**
 * bufferR - reads input into a buffer
 * @buffstruct: pointer to info_t struct
 * @Rbuffer: buffer for reading input
 * @bsize: pointer to size of buffer
 *
 * Return: number of bytes read, or -1 on failure
 */

ssize_t bufferR(info_t *buffstruct, char *Rbuffer, size_t *bsize)
{
	ssize_t res = 0;

	if (*bsize)
		return (0);
	res = read(buffstruct->readfd, Rbuffer, INPUT_BUFF);
	if (res >= 0)
		*bsize = res;
	return (res);
}

/**
 * callstr - reads input from a file descriptor and appends it to a string
 * @struct1: pointer to info_t struct containing file descriptor to read from
 * @pointr: pointer to pointer to string to append input to
 * @allocsize: pointer to size_t to keep track of allocated memory
 *
 * Return: the new size of the string on success, or -1 on failure
 */

int callstr(info_t *struct1, char **pointr, size_t *allocsize)
{
	static char ibuff[INPUT_BUFF];
	static size_t a, b;
	size_t g;
	ssize_t r = 0, s = 0;
	char *ppp = NULL, *np = NULL, *x;

	ppp = *pointr;
	if (ppp && allocsize)
		s = *allocsize;
	if (a == b)
		a = b = 0;

	r = bufferR(struct1, ibuff, &b);
	if (r == -1 || (r == 0 && b == 0))
		return (-1);

	x = charaloc(ibuff + a, '\n');
	g = x ? 1 + (unsigned int)(x - ibuff) : b;
	np = reallocMemory(ppp, s, s ? s + g : g + 1);
	if (!np) /* MALLOC FAILURE! */
		return (ppp ? free(ppp), -1 : -1);

	if (s)
		cat2str(np, ibuff + a, g - a);
	else
		copytext(np, ibuff + a, g - a + 1);

	s += g - a;
	a = g;
	ppp = np;

	if (allocsize)
		*allocsize = s;
	*pointr = ppp;
	return (s);
}

/**
 * blocksig - Prints prompt string and signals a new command input
 *
 * @num_of: unused integer parameter
 *
 * Description: This function is used as a signal handler to catch the
 * SIGINT signal sent by pressing Ctrl-C. It prints a new prompt string and
 * signals that a new command input is expected.
 */

void blocksig(__attribute__((unused))int num_of)
{
	printString("\n");
	printString("$ ");
	_putchar(BUFF_SHELL);
}
