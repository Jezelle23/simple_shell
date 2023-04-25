#include "customshell.h"

/**
 * cmdcheck - checks if is a command
 * @info: structure with info
 * @path: file path
 * Return: 1 if its a command, else 0
 */
int cmdcheck(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * cloneChars - clones characters
 * @pathstr: string of PATH
 * @start: initial index
 * @stop: ending index
 * Return: buffer of new pointer
 */
char *cloneChars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * pathSearch - finds this cmd in the PATH string
 * @info: structure with info
 * @pathstr: string of the PATH
 * @cmd: command to look for
 * Return: path of command, null when fail
 */
char *pathSearch(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && str_Prefix(cmd, "./"))
	{
		if (cmdcheck(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = cloneChars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (cmdcheck(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

