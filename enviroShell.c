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

/**
 * callenv - searches for an environment variable and returns its value
 * @info: pointer to a struct containing environmental variable information
 * @varEnv: the environment variable to search for
 *
 * Return: a pointer to the value of the environmental variable
 */
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
