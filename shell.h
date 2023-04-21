#ifndef SHELL_H
#define SHELL_H

/** ===== C Header Files =====  */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>


/** ===== Global Variables ===== */
extern char **environ;

/** ===== Structures ===== */

/**
 * strutct path_s - linked list for the paths in the PATH environment variable
 * @nname: path name;
 * @next: points to the next node
 *
 * Description: a structure for store paths defined in the environment variable
 * PATH
 */
typedef struct path_s
{
	char *name;
	struct path_s *next;
} path_t;

/** ===== End Structures ===== */


/** ===== Function Prototypes ===== */

/** === PATH Environment Variable Utility === */
int print_paths_list(const path_t *h);
path_t *add_path_end(path_t **head, char *path);
path_t *create_paths_list(void);
void free_paths_list(path_t *head);
char *_which(const char *filename);
char *_memset(char *s, char b, unsigned int n);

/** === Line Utility === */
char **split_line(char *line, char *delim);
char *resize_word(char **arr, char *word, int *word_size);
char **resize_arr(char **arr, int *arr_size, char *word);
void print_prompt(char *prompt);

/** === Environment Utility === */
char *_getenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);

/** === Execution Utility === */
int args_count(char **args);
void free_args(char **args);
void free_line(char *line);
void after_execute(char **args, char *prompt);
void handle_error_execute(char *cause);

#endif /* SHELL_H */
