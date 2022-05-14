/*
** EPITECH PROJECT, 2022
** fortytwo.sh
** File description:
** find_word
*/

#include <stddef.h>
#include <string.h>
#include "my_clear_str.h"

char *find_word(char *str, int *size)
{
    int index = 0;
    char *word = NULL;

    while (str[index] != ' ' && str[index] != '\0') {
        index ++;
    }
    word = strndup(str, index);
    *size = index;
    return (word);
}

char *find_word_quotes(char *str, int *size)
{
    int index = 1;
    char *word = NULL;

    while (str[index] != '"' && str[index] != '\0'
    && str[index] != '\'') {
        index ++;
    }
    word = strndup(&str[1], index - 1);
    *size = index + 1;
    return (word);
}
