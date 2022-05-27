/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** split str with shell def
*/

#include <stdbool.h>
#include <stdlib.h>
#include "my_puts.h"
#include "my_list.h"
#include "my_strings.h"
#include "mysh.h"

int check_if_field(int i, char *str, const char *delim,
    int *is);

static char *my_strfdcut(char *str, int start, int end)
{
    char *new = NULL;

    if (end < start) {
        return (NULL);
    }
    new = malloc(sizeof(char) * (end - start + 1));
    if (new == NULL) {
        return (NULL);
    }
    for (int i = start; i < end; i++) {
        new[i - start] = str[i];
    }
    new[end - start] = '\0';
    return (new);
}

list_t *my_strsplit(char *str, const char *delim)
{
    list_t *list = NULL;
    int last_index = 0;
    char *to_add = NULL;
    int is_in_quote = 0;
    int is_first = 0;

    if (str == NULL || delim == NULL) {
        return (NULL);
    }
    for (int i = 0; i <= my_strlen(str); i++) {
        if (check_if_field(i, str, delim, &is_in_quote) == true) {
            to_add = my_strfdcut(str, last_index, i);
        }
        if (to_add != NULL) {
            last_index = i + my_strlen(delim);
            list = split_str_add_to_list(list, to_add, &is_first);
            to_add = NULL;
        }
    }
    return (list);
}
