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
	char *line = NULL, **args = NULL, *delim = " \n", *prompt = "#cisfun$ ";
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
		if (!args[0])
			after_execute(args, prompt);
		else if (args_count(args) < 3)
		{
			pid = fork();
			if (pid == -1)
				handle_error_execute("fork");
			if (pid == 0)
			{
				if (execve(args[0], args, ep) == -1)
					handle_error_execute("./shell");
				else
					exit(EXIT_SUCCESS);
			}
			else
			{
				wait(&status);
				after_execute(args, prompt);
			}
		}
		else
		{
			printf("./shell: No such file or directory\n");
			after_execute(args, prompt);
		}
	}
	return (free_line(line), EXIT_SUCCESS);
}
