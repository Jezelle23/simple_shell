#include "customshell.h"

/**
 * isMultiDelim - checks multiple delimiters
 * @info: info structure
 * @buf: character buff
 * @p: index pointer
 * Return: 1 if multi delim, else 0
 */
int isMultiDelim(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->commandbuff = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->commandbuff = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->commandbuff = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * shouldChain - acorrding to status, check if we need to chain
 * @info: info struct
 * @buf: character buffer
 * @p: buff index ptr
 * @i: start of buffer
 * @len: buffer length
 * Return: Void
 */
void shouldChain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->commandbuff == CMD_AND)
	{
		if (info->result)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->commandbuff == CMD_OR)
	{
		if (!info->result)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * repalias - swaps alias to cmd
 * @info: info structure
 * Return: 1 if swapped, else 0
 */
int repalias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = retnode(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = charaloc(node->str, '=');
		if (!p)
			return (0);
		p = duplicateString(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * switchvar - switches variabls in token string
 * @info: info structure
 * Return: 1 if changed, else 0
 */
int switchvar(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!stringcomp(info->argv[i], "$?"))
		{
			switchString(&(info->argv[i]),
				duplicateString(convertfunction(info->result, 10, 0)));
			continue;
		}
		if (!stringcomp(info->argv[i], "$$"))
		{
			switchString(&(info->argv[i]),
				duplicateString(convertfunction(getpid(), 10, 0)));
			continue;
		}
		node = retnode(info->env, &info->argv[i][1], '=');
		if (node)
		{
			switchString(&(info->argv[i]),
				duplicateString(charaloc(node->str, '=') + 1));
			continue;
		}
		switchString(&info->argv[i], duplicateString(""));

	}
	return (0);
}

/**
 * switchString - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int switchString(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

