#include "shell.h"

/**
 * child_action - is called by a child process, executes a command-line and
 * handles error if any.
 *
 * Prototype: void parent_action(char **args, char **ep, char *bin);
 * @args: command-line to execute
 * @ep: a pointer to the environment of the program
 * @bin: executable
 */
void child_action(char **args, char **ep, char *bin)
{
	execve(bin, args, ep);
	perror("./shell");
	free_args(args);
	exit(EXIT_FAILURE);

}

/**
 * parent_action - is called by a parent process to wait for its children,
 * clean resources and displays a prompt for waiting a new command-line
 *
 * Prototype: void parent_action(char **args, char *bin, char *prompt,
 * int *status);
 *
 * @args: command-line to execute
 * @bin: executable
 * @prompt: prompt to display
 * @status: returned value by one of its children
 */
void parent_action(char **args, char *bin, char *prompt, int *status)
{
	wait(status);
	printf("%s", prompt);
	fflush(stdout);
	free(bin);
	free_args(args);
}

/**
 * not_executed - handles unknown executable
 * Prototype: void not_executed(char **args, char *prompt);
 * @args: command-line
 * @prompt: prompt to display
 */
void not_executed(char **args, char *prompt)
{
	fflush(stdout);
	printf("./shell: No such file or directory\n");
	print_prompt(prompt);
	free_args(args);
}
