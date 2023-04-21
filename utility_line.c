#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

/**
 * print_prompt - prints out a prompt based on a given string
 * Prototype: void print_prompt(char *prompt);
 * @prompt: string to print
 */
void print_prompt(char *prompt)
{
	if (!prompt)
		printf("$ ");
	else
	{
		if (isatty(STDIN_FILENO))
			printf("%s", prompt);
		if (prompt[strlen(prompt) - 1] != ' ')
			putchar(' ');
	}
}

/**
 * split_line - splits a string based a delimiter
 * split_line(char *line, char *delim);
 * @line: a string
 * @delim: a string used to separate elements in @line
 * Return: an array of strings, or NULL on failure
 */
char **split_line(char *line, char *delim)
{
	char **arr = NULL, *word = NULL;
	int i = 0, j = 0, k = 0, word_size = 10, arr_size = 10;

	if (!line)
		return (NULL);
	arr = malloc(arr_size * sizeof(char *));
	if (!arr)
		return (NULL);
	word = malloc(word_size * sizeof(char));
	if (!word)
		return (free(arr), NULL);
	for (i = 0; line[i]; i++)
	{
		while (line[i] && strchr(delim, line[i]) != 0)
			i++;
		if (!line[i])
			break;
		if (j >= word_size)
			word = resize_word(arr, word, &word_size);
		j = 0;
		while (line[i] && strchr(delim, line[i]) == 0)
		{
			word[j] = line[i];
			j++;
			i++;
			if (j >= word_size)
				word = resize_word(arr, word, &word_size);
		}
		word[j] = '\0';
		if (k >= arr_size)
			arr = resize_arr(arr, &arr_size, word);
		arr[k] = strdup(word);
		if (!arr[k])
			return (free(arr), free(word), NULL);
		k++;
	}
	if (!arr)
		return (free(arr), free(word), NULL);
	arr[k] = NULL;
	return (free(word), arr);
}

/**
 * resize_word - allocate more memory space to a string
 * Prototype: char *resize_word(char **arr, char *word, int word_size);
 * @arr: an array of strings
 * @word: a string to resize its length
 * @word_size: lenght of @word
 * Return: a pointer to the newly string allocated
 */
char *resize_word(char **arr, char *word, int *word_size)
{
	char *tmp_word = NULL;

	if (!arr || !word)
		return (NULL);
	(*word_size) *= 2;
	tmp_word = realloc(word, (*word_size) * sizeof(char));
	if (!tmp_word)
	{
		free(word);
		free(arr);
		return (NULL);
	}
	word = tmp_word;
	return (word);
}

/**
 * resize_arr - allocate more memory space to an array
 * Prototype: char **resize_arr(char **arr, int *arr_size, char *word);
 * @arr: an array of strings
 * @arr_size: current size of array
 * @word: a pointer used to hold each string of the array
 * Return: a pointer to newly array allocated
 */
char **resize_arr(char **arr, int *arr_size, char *word)
{
	char **tmp_arr = NULL;

	(*arr_size) *= 2;
	tmp_arr = realloc(arr, (*arr_size) * sizeof(char *));
	if (!tmp_arr)
	{
		free(word);
		free(arr);
		return (NULL);
	}
	arr = tmp_arr;
	return (arr);
}
