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
					handle_error_execute("fork");
				if (pid == 0)
				{
					execve(bin, args, ep);
					perror("./shell");
					free_args(args);
					exit(EXIT_FAILURE);
				}
				else
				{
					wait(&status);
					printf("%s", prompt);
					fflush(stdout);
					free(bin);
					free_args(args);
				}
			}
			else
			{
				printf("./shell: No such file or directory\n");
				free_args(args);
				print_prompt(prompt);
			}
		}
	}
	return (free_line(line), EXIT_SUCCESS);
}
