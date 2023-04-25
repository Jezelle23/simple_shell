#include"customshell.h"
/**
 * enviroInit - initializes a new environment variable
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

int _unsetenv(info_t *abcstruct, char *words)
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
