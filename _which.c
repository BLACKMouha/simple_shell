#include "shell.h"

/**
 * _which - looks for files in the current PATH
 * Prototype: char *_which(const char *filename);
 * @filename: executable file
 * Return: on success the first path of the executable, on failure NULL
 */
char *_which(const char *filename)
{
	char *path, *dir, *full_path;
	struct stat st;
	size_t len_dir, len_bin;

	if (!filename)
		return (NULL);

	if (filename[0] == '/')
	{
		if (stat(filename, &st) == 0)
			return (strdup(filename));
		else
			return (NULL);
	}
	path = strdup(getenv("PATH"));
	dir = strtok(path, ":");
	full_path = NULL;
	len_dir = 0;
	len_bin = strlen(filename);
	while (dir)
	{
		len_dir = strlen(dir);
		full_path = malloc((len_dir + len_bin + 2) * sizeof(char));
		if (!full_path)
			return (free(path), NULL);
		sprintf(full_path, "%s/%s", dir, filename);
		if (stat(full_path, &st) == 0)
			return (free(path), full_path);
		free(full_path);
		dir = strtok(NULL, ":");
	}
	return (free(path), NULL);
}
