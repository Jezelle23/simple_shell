#include "customshell.h"

/**
 * initialen - Initializes environment variables from command line arguments.
 * @potenargs: Pointer to a struct containing command line arguments.
 *
 * Return: 1 if successful, 0 if enviroInit() fails.
 */

int initialen(info_t *potenargs)
{
	if (potenargs->argc != 3)
	{
		errorout("Incorrect number of arguements\n");
		return (1);
	}
	if (enviroInit(potenargs, potenargs->argv[1], potenargs->argv[2]))
		return (0);
	return (1);
}

char *callenv(info_t *info, const char *varEnv)
{
	list_t *varNode = info->env;
	char *addnode;

	while (varNode)
	{
		addnode = str_Prefix(varNode->str, varEnv);
		if (addnode && *addnode)
			return (addnode);
		varNode = varNode->next;
	}
	return (NULL);
}


/**
 * poplinkedenv - Populates a linked list with environment variables.
 * @popstruct: Pointer to a struct to store the linked list.
 *
 * Return: 0 upon success.
 */

int poplinkedenv(info_t *popstruct)
{
	list_t *popnode = NULL;
	size_t popvar;

	for (popvar = 0; environ[popvar]; popvar++)
		node_appendLast(&popnode, environ[popvar], 0);
	popstruct->env = popnode;
	return (0);
}

/**
 * remenviroV - Removes environment variables from a struct.
 * @structenviro: Pointer to a struct containing environment variables.
 *
 * Return: 0 upon success, 1 if there are too few arguments.
 */

int remenviroV(info_t *structenviro)
{
	int x;

	if (structenviro->argc == 1)
	{
		errorout("Less arguments \n");
		return (1);
	}
	for (x = 1; x <= structenviro->argc; x++)
		delenviro(structenviro, structenviro->argv[x]);

	return (0);
}

/**
 * currenviro - Displays current environment variables.
 * @info_enviro: Pointer to a struct containing environment variables.
 *
 * Return: 0 upon success.
 */

int currenviro(info_t *info_enviro)
{
	displaydet(info_enviro->env);
	return (0);
}

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
 * @allocsize: pointer to size_t to keep track of allocated memory size for string
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

/**
 * enviroInit - initializes a new environment variable or updates an existing one
 *
 * @envirostruct: pointer to struct containing environment information
 * @varaen: name of environment variable to initialize or update
 * @envirovalue: value to assign to the environment variable
 *
 * Return: 0 on success, 1 on failure
 */

int enviroInit(info_t *envirostruct, char *varaen, char *envirovalue)
{
	char *enbuff = NULL;
	list_t *endnode;
	char *endp;

	if (!varaen || !envirovalue)
		return (0);

	enbuff = malloc(_strlen(varaen) + _strlen(envirovalue) + 2);
	if (!enbuff)
		return (1);
	copyString(enbuff, varaen);
	_strcat(enbuff, "=");
	_strcat(enbuff, envirovalue);
	endnode = envirostruct->env;
	while (endnode)
	{
		endp = str_Prefix(endnode->str, varaen);
		if (endp && *endp == '=')
		{
			free(endnode->str);
			endnode->str = enbuff;
			envirostruct->changedenviro = 1;
			return (0);
		}
		endnode = endnode->next;
	}
	node_appendLast(&(envirostruct->env), enbuff, 0);
	free(enbuff);
	envirostruct->changedenviro = 1;
	return (0);
}

/**
 * delenviro - deletes an environment variable from the list
 * @abcstruct: a pointer to the info_t struct
 * @words: the variable name to be deleted
 *
 * Return: 1 if the node was deleted, 0 otherwise
 */

int delenviro(info_t *abcstruct, char *words)
{
	list_t *environode = abcstruct->env;
	size_t ves = 0;
	char *spoint;

	if (!environode || !words)
		return (0);

	while (environode)
	{
		spoint = str_Prefix(environode->str, words);
		if (spoint && *spoint == '=')
		{
			abcstruct->changedenviro = deletenodeI(&(abcstruct->env), ves);
			ves = 0;
			environode = abcstruct->env;
			continue;
		}
		environode = environode->next;
		ves++;
	}
	return (abcstruct->changedenviro);
}

/**
 * stringcopyenv - Copies the environment variables to a new array of strings
 * @potarg: The struct containing the environment variables
 *
 * Return: A double pointer to an array of strings containing the environment
 * variables, or NULL on failure.
 */

char **stringcopyenv(info_t *potarg)
{
	if (!potarg->environ || potarg->changedenviro)
	{
		potarg->environ = textlist(potarg->env);
		potarg->changedenviro = 0;
	}

	return (potarg->environ);
}

/**
 * releasew - frees the memory used by infostruct
 * @infostruct: pointer to info_t struct
 * @freeall: flag to determine whether all memory should be freed
 *
 * Return: void
 */

void releasew(info_t *infostruct, int freeall)
{
	freestr(infostruct->argv);
	infostruct->argv = NULL;
	infostruct->path = NULL;
	if (freeall)
	{
		if (!infostruct->membuff)
			free(infostruct->arg);
		if (infostruct->env)
			freenodes(&(infostruct->env));
		if (infostruct->history)
			freenodes(&(infostruct->history));
		if (infostruct->alias)
			freenodes(&(infostruct->alias));
		freestr(infostruct->environ);
			infostruct->environ = NULL;
		pointfree((void **)infostruct->membuff);
		if (infostruct->readfd > 2)
			close(infostruct->readfd);
		_putchar(BUFF_SHELL);
	}
}


/**
 * set_stone - Sets the fileword and splits the argument string into an
 * argument vector (argv) in the given info struct. It also updates the argc
 * member of the struct.
 *
 * @vex: The info struct to modify.
 * @argvec: The argument vector to use.
 */


void set_stone(info_t *vex, char **argvec)
{
	int var = 0;

	vex->fileword = argvec[0];
	if (vex->arg)
	{
		vex->argv = splitDelStr(vex->arg, " \t");
		if (!vex->argv)
		{

			vex->argv = malloc(sizeof(char *) * 2);
			if (vex->argv)
			{
				vex->argv[0] = duplicateString(vex->arg);
				vex->argv[1] = NULL;
			}
		}
		for (var = 0; vex->argv && vex->argv[var]; var++)
			;
		vex->argc = var;

		repalias(vex);
		switchvar(vex);
	}
}
/**
 * info_init - Initializes a struct of type info_t
 *
 * @struct_address: Pointer to the address of a struct of type info_t
 */
void info_init(info_t *struct_address)
{
	struct_address->arg = NULL;
	struct_address->argv = NULL;
	struct_address->path = NULL;
	struct_address->argc = 0;
}
