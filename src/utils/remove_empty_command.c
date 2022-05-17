/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** remove empty commands
*/

#include <stdlib.h>
#include "my_list.h"
#include "my_strings.h"
#include "mysh.h"

list_t *remove_empty_commands(list_t *list)
{
    list_t *new = NULL;

    if (list == NULL) {
        return (NULL);
    }
    for (int i = 0; i < list_t_len(list); i++, list = list->next) {
        if (list->data != NULL && my_strcmp(list->data, "") != 0) {
            new = list_t_add(new, list->separator, my_strdup(list->data),
            &free);
        }
    }
    list_t_destroy(list);
    return (new);
}
