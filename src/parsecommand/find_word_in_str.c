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

static int find_index_of_d_quotes(char *str)
{
    int index = my_strlen(str);

    while (str[index] != '\"' && index > 0) {
        index -= 1;
    }
    index += 1;
    return (index);
}

static int find_index_of_s_quotes(char *str)
{
    int index = my_strlen(str);

    while (str[index] != '\'' && index > 0) {
        index -= 1;
    }
    index += 1;
    return (index);
}

char *find_word_quotes(char *str, int *size)
{
    int index = 0;
    char *word = NULL;

    if (str == NULL || size == NULL)
        return (NULL);
    if (str[0] == '\"') {
        index = find_index_of_d_quotes(str);
    } else {
        index = find_index_of_s_quotes(str);
    }
    word = my_strndup(str, index);
    *size = index;
    return (word);
}
