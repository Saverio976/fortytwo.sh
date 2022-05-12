/*
** EPITECH PROJECT, 2022
** LIBLIST
** File description:
** add elem
*/

#include <stdlib.h>
#include "my_list.h"

list_t *list_t_add(list_t *list, void *data, void (*destroy)(void *data))
{
    list_t *new = NULL;

    if (data == NULL && destroy != NULL) {
        return (list);
    }
    new = malloc(sizeof(list_t));
    if (new == NULL) {
        return (list);
    }
    new->data = data;
    new->destroy = destroy;
    new->last = (list != NULL) ? list->last : new;
    new->next = (list != NULL) ? list : new;
    if (list != NULL) {
        list->last->next = new;
        list->last = new;
        return (list);
    }
    return (new);
}
