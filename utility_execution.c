#include "shell.h"

/**
 * after_execute - common statements to execute after execve returns
 * Prototype: void after_execute(char **args, char *prompt);
 * @args: an array of strings holding the different elements of a command line
 * @prompt: string to use as prompt to print
 */
void after_execute(char **args, char *prompt)
{
	free_args(args);
	print_prompt(prompt);
}

/**
 * handle_error_execute - handles error during execution
 * Prototype: void handle_error_execute(char *cause);
 * @cause: the function name related to the error;
 */
void handle_error_execute(char *cause)
{
	perror(cause);
	exit(EXIT_FAILURE);
}
