#include "shell.h"

/**
 * main - Entry point
 * Prototye: int main(ac, char **av, char **ep);
 * @ac: number of items in @av
 * @av: array of strings for arguments passed to the program
 * @ep: array of strings for environment variables  passed to the program
 * Return: On success EXIT_SUCCESS, on failure EXIT_FAILURE.
 */

int main(int ac, char **av, char **ep)
{
	char *line = NULL, **args = NULL, *delim = " \n", *prompt = "$ ";
	char *bin = NULL;
	size_t n = 0;
	ssize_t chars = 0;
	int status;
	pid_t pid;

	(void) av;
	(void) ac;
	print_prompt(prompt);
	while ((chars = getline(&line, &n, stdin)) != -1)
	{
		args = split_line(line, delim);
		if (args == NULL || args[0] == NULL)
		{
			print_prompt(prompt);
			fflush(stdout);
		}
		else
		{
			bin = _which(args[0]);
			if (bin != NULL)
			{
				pid = fork();
				if (pid == -1)
				{
					perror("fork");
					exit(EXIT_FAILURE);
				}
				if (pid == 0)
					child_action(args, ep, bin);
				else
					parent_action(args, bin, prompt, &status);
			}
			else
				not_executed(args, prompt);
		}
	}
	return (free_line(line), EXIT_SUCCESS);
}
