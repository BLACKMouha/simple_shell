#include "shell.h"

/**
 * args_count - counts the number of elements in a command line
 * Prototype: int args_count(char **args);
 * @args: an array of strings holding the different elements of a command line
 * Return: an integer, the number of elements in a command line
 */
int args_count(char **args)
{
	int i;

	for (i = 0; args[i]; i++)
		;
	return (i);
}
