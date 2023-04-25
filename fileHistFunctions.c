#include "customshell.h"

/**
 * getFileHist - fetches history of file
 * @info: info structure
 * Return: string with history
 */

char *getFileHist(info_t *info)
{
	char *buf, *dir;

	dir = callenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	copyString(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * histWrite - appends to or creates file for history
 * @info: info structure
 * Return: 1 on success -1 for fail
 */
int histWrite(info_t *info)
{
	ssize_t fd;
	char *filename = getFileHist(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		displayin(node->str, fd);
		dispfd('\n', fd);
	}
	dispfd(BUFF_SHELL, fd);
	close(fd);
	return (1);
}

/**
 * histRead - history reading for file
 * @info: info structure
 * Return: count on success, else
 */
int histRead(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = getFileHist(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			histListBuild(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		histListBuild(info, buf + last, linecount++);
	free(buf);
	info->historycount = linecount;
	while (info->historycount-- >= HIST_MAX)
		deletenodeI(&(info->history), 0);
	histNumbAssign(info);
	return (info->historycount);
}

/**
 * histListBuild - builds entery for hist linkedlist
 * @info: info structure for args
 * @buf: char buffer
 * @linecount: history count of lines
 * Return: Always 0
 */
int histListBuild(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	node_appendLast(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * histNumbAssign - reassigns number to history linklist after edit
 * @info: info struct with args
 * Return: history count
 */
int histNumbAssign(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->historycount = i);
}

