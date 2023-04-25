#include "customshell.h"

/**
 * displayHist - Displays the command history.
 * @historyStruct: Pointer to info_t struct.
 *
 * Return: 0 on success.
 */

int displayHist(info_t *historyStruct)
{
	displaydet(historyStruct->history);
	return (0);
}

/**
 * setAtostring - sets a string
 * @index: info structure
 * @stringA: a string
 *
 * Return: Returns 1 on success, 0 otherwise
 */

int setAtostring(info_t *index, char *stringA)
{
	char *ABC, x;
	int result;

	ABC = charaloc(stringA, '=');
	if (!ABC)
		return (1);
	x = *ABC;
	*ABC = 0;
	result = deletenodeI(&(index->alias),
		getnodeI(index->alias, retnode(index->alias, stringA, -1)));
	*ABC = x;
	return (result);
}

/**
 * setAlias_toStr - sets an alias to a given value
 * @Astruct: pointer to a struct containing alias information
 * @aliasstring: the string representing the alias to set
 *
 * Return: 1 on failure, 0 on success
 */

int setAlias_toStr(info_t *Astruct, char *aliasstring)
{
	char *SetS;

	SetS = charaloc(aliasstring, '=');
	if (!SetS)
		return (1);
	if (!*++SetS)
		return (setAtostring(Astruct, aliasstring));

	setAtostring(Astruct, aliasstring);
	return (node_appendLast(&(Astruct->alias), aliasstring, 0) == NULL);
}

/**
 * displayalias - displays an alias
 * @aliasnode: pointer to a node in a linked list of aliases
 *
 * Return: 0 on success, 1 on failure
 */

int displayalias(list_t *aliasnode)
{
	char *text = NULL, *vara = NULL;

	if (aliasnode)
	{
		text = charaloc(aliasnode->str, '=');
		for (vara = aliasnode->str; vara <= text; vara++)
			_putchar(*vara);
		_putchar('\'');
		printString(text + 1);
		printString("'\n");
		return (0);
	}
	return (1);
}

/**
 * copyAlias - copies an alias
 * @consf: pointer to a struct containing command information
 *
 * Return: 0 on success
 */

int copyAlias(info_t *consf)
{
	int j = 0;
	char *point = NULL;
	list_t *nodecopy = NULL;

	if (consf->argc == 1)
	{
		nodecopy = consf->alias;
		while (nodecopy)
		{
			displayalias(nodecopy);
			nodecopy = nodecopy->next;
		}
		return (0);
	}
	for (j = 1; consf->argv[j]; j++)
	{
		point = charaloc(consf->argv[j], '=');
		if (point)
			setAlias_toStr(consf, consf->argv[j]);
		else
			displayalias(retnode(consf->alias, consf->argv[j], '='));
	}

	return (0);
}
