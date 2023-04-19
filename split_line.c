#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

char **split_line(char *line, char *delim)
{
  char **arr = NULL;
  char *tmp_word = NULL, *word = NULL, **tmp_arr = NULL;
  int i = 0, j = 0, k = 0;
  int word_size = 10;
  int arr_size = 10;

  if (!line)
    return (NULL);

  arr = malloc(arr_size * sizeof(char *));
  if (!arr)
    return (NULL);

  word = calloc(word_size, sizeof(char));
  if (!word)
  {
    free(arr);
    return (NULL);
  }

  for (i = 0; line[i]; i++)
  {
    while (line[i] && strchr(delim, line[i]) != 0)
      i++;

    if (!line[i])
      break;

    if (j >= word_size)
    {
      word_size *= 2;
      tmp_word= realloc(word, word_size * sizeof(char));
      if (!tmp_word)
      {
        free(word);
        free(arr);
        return (NULL);
      }
      word = tmp_word;
    }

    j = 0;
    while (line[i] && strchr(delim, line[i]) == 0)
    {
      word[j] = line[i];
      i++;
      j++;

      if (j >= word_size)
      {
        word_size *= 2;
        tmp_word = realloc(word, word_size * sizeof(char));
        if (!tmp_word)
        {
          free(word);
          free(arr);
          return (NULL);
        }
        word = tmp_word;
      }
    }

    word[j] = '\0';

    if (k >= arr_size)
    {
      arr_size *= 2;
      tmp_arr = realloc(arr, arr_size * sizeof(char *));
      if (!tmp_arr)
      {
        free(word);
        free(arr);
        return (NULL);
      }
      arr = tmp_arr;
    }

    arr[k] = strdup(word);

    if (!arr[k])
    {
      free(word);
      free(arr);
      return (NULL);
    }

    k++;
  }

  arr[k] = NULL;

  free(word);

  return (arr);
}
