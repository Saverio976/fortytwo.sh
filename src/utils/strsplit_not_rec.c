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

int check_if_delim(int i, char *str, const char *delim)
{
    if (my_strstartswith(str + i, delim) == 0 || str[i] == 0) {
        return ((str[i] == 0) ? true : false);
    }
    if (i == 0) {
        return (true);
    }
    if (str[i - 1] != '\\') {
        return (true);
    } else if (i > 1 && str[i - 2] == '\\') {
        return (false);
    }
    return (true);
}

int check_if_field(int i, char *str, const char *delim,
    int *is)
{
    if (my_strcontainc("\"'", str[i]) == 1 && ((str[i] == '"' && *is == '"') ||
            (str[i] == '\'' && *is == '\'') || *is == 0)) {
        *is = (*is == 0) ? str[i] : 0;
    }
    if (*is != 0) {
        return (false);
    }
    return (check_if_delim(i, str, delim));
}

static char *compute_str_to_add(char *str)
{
    char *new = NULL;

    if (str == NULL) {
        return (NULL);
    }
    new = my_strdup(str);
    if (new == NULL) {
        return (str);
    }
    if (new[0] == '\0') {
        free(new);
        free(str);
        return (NULL);
    }
    free(str);
    return (new);
}

list_t *strsplit_not_rec(char *str, const char *delim)
{
    list_t *list = NULL;
    int last_index = 0;
    char *to_add = NULL;
    int is_in_quote = 0;

    if (str == NULL || delim == NULL) {
        return (NULL);
    }
    for (int i = 0; i <= my_strlen(str); i++) {
        if (check_if_field(i, str, delim, &is_in_quote)) {
            to_add = my_strfdcut(str, last_index, i);
        }
        if (to_add != NULL) {
            last_index = i + my_strlen(delim);
            list = list_t_add(list, 0, compute_str_to_add(to_add), &free);
            to_add = NULL;
        }
    }
    return (list);
}
