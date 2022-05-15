/*
** EPITECH PROJECT, 2022
** fortytwo.sh
** File description:
** find_word
*/

#include <stddef.h>
#include "my_clear_str.h"
#include "my_strings.h"

char *find_word(char *str, int *size)
{
    int index = 0;
    char *word = NULL;

    if (str == NULL || size == NULL)
        return (NULL);
    while (str[index] != ' ' && str[index] != '\0') {
        index += 1;
    }
    word = my_strndup(str, index);
    *size = index;
    return (word);
}

char *find_word_quotes(char *str, int *size)
{
    int index = 1;
    char *word = NULL;

    if (str == NULL || size == NULL)
        return (NULL);
    while (str[index] != '"' && str[index] != '\0'
    && str[index] != '\'') {
        index += 1;
    }
    word = my_strndup(&str[1], index - 1);
    *size = index + 1;
    return (word);
}
