#ifndef SHELL_H
#define SHELL_H

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

/** === PATH Handler === */
int print_paths_list(const path_t *h);
path_t *add_path_end(path_t **head, char *path);
path_t *create_paths_list(void);
void free_paths_list(path_t *head);

/** === Line Utility === */
char **split_line(char *line, char *delim);

/** === Environment Handler === */
char *_getenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);

#endif /* SHELL_H */
