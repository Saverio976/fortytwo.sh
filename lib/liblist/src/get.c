/*
** EPITECH PROJECT, 2022
** LIBLIST
** File description:
** get value from index
*/

#include <stddef.h>
#include "my_list.h"

list_t *list_t_get_node(list_t *list, int index)
{
    list_t *tmp = NULL;

    if (list == NULL) {
        return (NULL);
    }
    tmp = list;
    for (int i = 0; i <= index; i++) {
        if (i == index) {
            return (tmp);
        }
        tmp = tmp->next;
    }
    return (NULL);
}

void *list_t_get_data(list_t *list, int index)
{
    list_t *tmp = NULL;

    tmp = list_t_get_node(list, index);
    if (tmp == NULL) {
        return (NULL);
    }
    return (tmp->data);
}
