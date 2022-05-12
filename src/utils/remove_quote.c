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
    int index = 0;

    if (list == NULL) {
        return (NULL);
    }
    new = malloc(sizeof(char) * (len + 1));
    if (new == NULL) {
        return (NULL);
    }
    new[len] = '\0';
    for (int i = 0; i < list_t_len(list); i++, list = list->next) {
        for (int in = 0; ((char *) list->data)[in] != '\0'; in++) {
            new[index++] = ((char *) list->data)[in];
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
