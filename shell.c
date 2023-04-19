#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

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
 * main - Entry point
 * Prototye: int main(ac, char **av, char **ep);
 * @ac: number of items in @av
 * @av: array of strings for arguments passed to the program
 * @ep: array of strings for the environment variables
 * Return: On success EXIT_SUCCESS, on failure EXIT_FAILURE.
 */
int main(int ac, char **av, char **ep)
{
	char *lineptr, **cmd, *delim;
	size_t n;
	ssize_t chars;
	int status;
	pid_t pid;

	delim = " \n";
	lineptr = NULL;
	n = 0;
	chars = 0;
	cmd = NULL;
	printf("$ ");
	while ((chars = getline(&lineptr, &n, stdin)) != -1)
	{
		cmd = split_line(lineptr, delim);
		if (cmd_items(cmd) == 1)
		{
			pid = fork();
			if (pid == -1)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
			if (pid == 0)
			{
				if (execve(cmd[0], cmd, ep) == -1)
				{
					perror("./shell");
					exit(EXIT_FAILURE);
				}
				else
					exit(EXIT_SUCCESS);
			}
			else
			{
				wait(&status);
				if (isatty(STDIN_FILENO))
					printf("$ ");
			}
		}
		else
			printf("./shell: No such file or directory\n$ ");
	}
	return (EXIT_SUCCESS);
}
