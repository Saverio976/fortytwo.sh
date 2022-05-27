/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** remove quote in arguments
*/

#include <stdlib.h>
#include "my_list.h"
#include "mysh.h"
#include "my_puts.h"
#include "my_strings.h"

static int get_len(list_t *list)
{
    int len = 0;

    if (list == NULL) {
        return (0);
    }
    for (int i = 0; i < list_t_len(list); i++, list = list->next) {
        len += my_strlen(list->data);
    }
    return (len);
}

static char *create_new_str(list_t *list, int len)
{
    char *new = NULL;
    char *tmp = NULL;

    if (list == NULL) {
        return (NULL);
    }
    new = my_calloc(len + 1);
    if (new == NULL) {
        return (NULL);
    }
    for (int i = 0; i < list_t_len(list); i++, list = list->next) {
        tmp = my_strstrip(list->data, "'\"");
        my_strcat(new, tmp);
        if (tmp != NULL) {
            free(tmp);
        }
    }
    return (new);
}

static char *remove_quote_delim(char *str, const char *delim)
{
    list_t *list = NULL;
    int len = 0;
    char *new = NULL;

    if (str == NULL) {
        return (NULL);
    }
    list = strsplit_not_rec(str, delim);
    if (list == NULL) {
        return (str);
    }
    len = get_len(list);
    new = create_new_str(list, len);
    list_t_destroy(list);
    if (new == NULL) {
        return (str);
    }
    free(str);
    return (new);
}

char *remove_quotes(char *str)
{
    char *new = NULL;

    new = remove_quote_delim(str, "\"");
    new = remove_quote_delim(new, "\'");
    return (new);
}

char **remove_quotes_command(char **arr)
{
    if (arr == NULL) {
        return (NULL);
    }
    for (int i = 0; arr[i] != NULL; i++) {
        arr[i] = remove_quotes(arr[i]);
    }
    return (arr);
}
