#include "customshell.h"

/**
 * deletenodeI - clears a node of given index
 * @headNode: first node pointer
 * @index: node index to clear
 * Return: 1 for success else 0
 */
int deletenodeI(list_t **headNode, unsigned int index)
{
	list_t *nodePrev;
	list_t *node;
	unsigned int x = 0;

	if (!headNode || !*headNode)
		return (0);

	if (!index)
	{
		node = *headNode;
		*headNode = (*headNode)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *headNode;
	while (node)
	{
		if (x == index)
		{
			nodePrev->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		x++;
		nodePrev = node;
		node = node->next;
	}
	return (0);
}

/**
 * freenodes - clears list
 * @head_ptr: pointer for first node of list
 * Return: void
 */
void freenodes(list_t **head_ptr)
{
	list_t *headNode;
	list_t *node;
	list_t *nextNode;

	if (!head_ptr || !*head_ptr)
		return;
	headNode = *head_ptr;
	node = headNode;
	while (node)
	{
		nextNode = node->next;
		free(node->str);
		free(node);
		node = nextNode;
	}
	*head_ptr = NULL;
}

/**
 * displaydet - print linked list components
 * @headNode: pointer to head of list
 * Return: list length
 */
size_t displaydet(const list_t *headNode)
{
	size_t x = 0;

	while (headNode)
	{
		printString(convertfunction(headNode->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		printString(headNode->str ? headNode->str : "(nil)");
		printString("\n");
		headNode = headNode->next;
		x++;
	}
	return (x);
}

/**
 * retnode - finds node of list with string to match
 * @node: pointer to head of list
 * @prefix: string to search for
 * @c: char after searched string
 * Return: node that matches else null
 */
list_t *retnode(list_t *node, char *prefix, char c)
{
	char *pt = NULL;

	while (node)
	{
		pt = str_Prefix(node->str, prefix);
		if (pt && ((c == -1) || (*pt == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * getnodeI - gets node index
 * @headNode: pointer to head of list
 * @node: node pointer of index
 * Return: node index or -1
 */
ssize_t getnodeI(list_t *headNode, list_t *node)
{
	size_t x = 0;

	while (headNode)
	{
		if (headNode == node)
			return (x);
		headNode = headNode->next;
		x++;
	}
	return (-1);
}

