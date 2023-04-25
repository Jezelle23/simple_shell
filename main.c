#include "customshell.h"

/**
 * main - main function
 * @ac: argc
 * @av: argv
 * Return: 0 when success, else 1
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				errorout(av[0]);
				errorout(": 0: Can't open ");
				errorout(av[1]);
				displaye('\n');
				displaye(BUFF_SHELL);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	poplinkedenv(info);
	histRead(info);
	shellLoop(info, av);
	return (EXIT_SUCCESS);
}

