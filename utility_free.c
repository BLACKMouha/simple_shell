#include "shell.h"

/**
 * free_args - free an array of strings
 * Prototype: void free_args(char **args);
 * @args: an array of strings holding the different elements of a command line
 */
void free_args(char **args)
{
	int i;

	for (i = 0; args[i]; i++)
		free(args[i]);
	free(args);
}

/**
 * free_line - free a pointer to a string
 * Prototype: void free_line(char *line);
 * @line: pointer to string to free
 */
void free_line(char *line)
{
	free(line);
}
