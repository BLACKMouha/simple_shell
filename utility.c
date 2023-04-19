#include "shell.h"
#include <stdlib.h>

/**
 * cmd_items - counts the number of elemnts in a command line
 * Prototype: int cmd_items(char **cmd);
 * @cmd: command line
 * Return: an integer, the number of elements in a command line
 */
int cmd_items(char **cmd)
{
	int i;

	for (i = 0; cmd[i]; i++)
		;
	return (i);
}

/**
 * free_cmd - free an array of string
 * Prototype: void free_cmd(char **cmd);
 * @cmd: array of string to free
 */
void free_cmd(char **cmd)
{
	int i;

	for (i = 0; cmd[i]; i++)
		free(cmd[i]);
	free(cmd);
}
