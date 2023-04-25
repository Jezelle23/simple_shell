#include "customshell.h"

/**
 * shellEscape - Handles the 'exit' command and exits the shell
 * @structexit: Pointer to info_t struct
 * Return: -2 if exit is valid, otherwise 1
 */

int shellEscape(info_t *structexit)
{
	int check_shellex;

	if (structexit->argv[1])
	{
		check_shellex = convString2int(structexit->argv[1]);
		if (check_shellex == -1)
		{
			structexit->result = 2;
			display_errmsg(structexit, "Error! Unknown number: ");
			errorout(structexit->argv[1]);
			displaye('\n');
			return (1);
		}
		structexit->errorInt = convString2int(structexit->argv[1]);
		return (-2);
	}
	structexit->errorInt = -1;
	return (-2);
}
/**
 * directChange - changes the current directory of the shell
 * @info: pointer to struct of info
 *
 * Return: 0 on success, 1 on failure
 */

int directChange(info_t *info)
{
	char *var1, *direct, direcBuffer[1024];
	int currentdir;

	var1 = getcwd(direcBuffer, 1024);
	if (!var1)
		printString("TO DO: >> getcwd failure message here <<\n");
	if (!info->argv[1])
	{
		direct = callenv(info, "home=");
		if (!direct)
			currentdir = chdir((direct = callenv(info, "pwd=")) ? direct : "/");
		else
			currentdir = chdir(direct);
	}
	else if (stringcomp(info->argv[1], "-") == 0)
	{
		if (!callenv(info, "previous pwd="))
		{
			printString(var1);
			_putchar('\n');
			return (1);
		}
		printString(callenv(info, "previous pwd=")), _putchar('\n');
		currentdir = chdir((direct = callenv(info, "previous pwd=")) ? direct : "/");
	}
	else
		currentdir = chdir(info->argv[1]);
	if (currentdir == -1)
	{
		display_errmsg(info, "Error. Can not cd to ");
		errorout(info->argv[1]), displaye('\n');
	}
	else
	{
		enviroInit(info, "previous pwd", callenv(info, "pwd="));
		enviroInit(info, "PWD", getcwd(direcBuffer, 1024));
	}
	return (0);
}

/**
 * change_currP - function that changes the current process
 * @CurrInfo: pointer to struct of information
 *
 * Return: Always 0
 */

int change_currP(info_t *CurrInfo)
{
	char **argument_A;

	argument_A = CurrInfo->argv;
	printString("help call works. Function not yet implemented \n");
	if (0)
		printString(*argument_A);
	return (0);
}

