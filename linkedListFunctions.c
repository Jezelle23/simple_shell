#include "customshell.h"

/**
 * getListlen - gets linked list length
 * @headNode: pointer to head of list
 * Return: list length
 */
size_t getListlen(const list_t *headNode)
{
	size_t x = 0;

	while (headNode)
	{
		headNode = headNode->next;
		x++;
	}
	return (x);
}

/**
 * textlist - gets the str array of a linkedlist
 * @headNode: pointer to head of list
 * Return: string array
 */
char **textlist(list_t *headNode)
{
	list_t *node = headNode;
	size_t x = getListlen(headNode), y;
	char *str;
	char **ppstr;

	if (!headNode || !x)
		return (NULL);
	ppstr = malloc(sizeof(char *) * (x + 1));
	if (!ppstr)
		return (NULL);
	for (x = 0; node; node = node->next, x++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (y = 0; y < x; y++)
				free(ppstr[y]);
			free(ppstr);
			return (NULL);
		}

		str = copyString(str, node->str);
		ppstr[x] = str;
	}
	ppstr[x] = NULL;
	return (ppstr);
}

/**
 * node_append - appends a node to start of list
 * @head: first node pointer
 * @str: string of node
 * @num: index of node
 * Return: list size
 */
list_t *node_append(list_t **head, const char *str, int num)
{
	list_t *headNew;

	if (!head)
		return (NULL);
	headNew = malloc(sizeof(list_t));
	if (!headNew)
		return (NULL);
	setMemory((void *)headNew, 0, sizeof(list_t));
	headNew->num = num;
	if (str)
	{
		headNew->str = duplicateString(str);
		if (!headNew->str)
		{
			free(headNew);
			return (NULL);
		}
	}
	headNew->next = *head;
	*head = headNew;
	return (headNew);
}

/**
 * node_appendLast - appends node to end of list
 * @head: first node adress pointer
 * @str: string of node
 * @num: index of node
 * Return: size of list
 */
list_t *node_appendLast(list_t **head, const char *str, int num)
{
	list_t *node;
	list_t *nodeNew;

	if (!head)
		return (NULL);

	node = *head;
	nodeNew = malloc(sizeof(list_t));
	if (!nodeNew)
		return (NULL);
	setMemory((void *)nodeNew, 0, sizeof(list_t));
	nodeNew->num = num;
	if (str)
	{
		nodeNew->str = duplicateString(str);
		if (!nodeNew->str)
		{
			free(nodeNew);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = nodeNew;
	}
	else
		*head = nodeNew;
	return (nodeNew);
}

/**
 * strList_print - print linked list string value
 * @headNode: first node pointer
 * Return: list size
 */
size_t strList_print(const list_t *headNode)
{
	size_t li = 0;

	while (headNode)
	{
		printString(headNode->str ? headNode->str : "(nil)");
		printString("\n");
		headNode = headNode->next;
		li++;
	}
	return (li);
}

