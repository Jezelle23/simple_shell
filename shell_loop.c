#include "customshell.h"

/**
 * shellLoop - main shell loop
 * @info: info struct
 * @av: vector of args
 * Return: 0 when succeded , 1 when fail otherwise ecode
 */
int shellLoop(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		info_init(info);
		if (shelli(info))
			printString("$ ");
		displaye(BUFF_SHELL);
		r = lineneg(info);
		if (r != -1)
		{
			set_stone(info, av);
			builtin_ret = getBIcmd(info);
			if (builtin_ret == -1)
				getCommand(info);
		}
		else if (shelli(info))
			_putchar('\n');
		releasew(info, 0);
	}
	histWrite(info);
	releasew(info, 1);
	if (!shelli(info) && info->result)
		exit(info->result);
	if (builtin_ret == -2)
	{
		if (info->errorInt == -1)
			exit(info->result);
		exit(info->errorInt);
	}
	return (builtin_ret);
}

/**
 * getBIcmd - gets a built in command
 * @info: info structure
 * Return: 0 if success excuted, -1 if doesn't exit
 *			 1 if found & fail , -2 when exiting
 */
int getBIcmd(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"cd", directChange},
		{"alias", copyAlias},
		{"exit", shellEscape},
		{"help", change_currP},
		{"history", displayHist},
		{"environment", currenviro},
		{"setenvironment", initialen},
		{"remenvironment", remenviroV},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (stringcomp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * getCommand - get command path
 * @info: info structure
 * Return: void
 */
void getCommand(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->countl == 1)
	{
		info->line_count++;
		info->countl = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!shell_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = pathSearch(info, callenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		forkCommand(info);
	}
	else
	{
		if ((shelli(info) || callenv(info, "PATH=")
			|| info->argv[0][0] == '/') && cmdcheck(info, info->argv[0]))
			forkCommand(info);
		else if (*(info->arg) != '\n')
		{
			info->result = 127;
			display_errmsg(info, "not found\n");
		}
	}
}

/**
 * forkCommand - forks command to run
 * @info: info structure
 * Return: void
 */
void forkCommand(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, stringcopyenv(info)) == -1)
		{
			releasew(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->result));
		if (WIFEXITED(info->result))
		{
			info->result = WEXITSTATUS(info->result);
			if (info->result == 126)
				display_errmsg(info, "Permission denied\n");
		}
	}
}

