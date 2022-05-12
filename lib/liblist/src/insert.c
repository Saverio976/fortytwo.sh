/*
** EPITECH PROJECT, 2022
** LIBLIST
** File description:
** insert data
*/

#include <stddef.h>
#include <stdlib.h>
#include "my_list.h"

static list_t *update_link(list_t *list, list_t *new, int status)
{
    if (list == NULL) {
        return (new);
    }
    new->next = list;
    new->last = list->last;
    list->last->next = new;
    list->last = new;
    if (status == 0) {
        return (new);
    } else if (status == 1) {
        return (list);
    }
    return (list);
}

list_t *list_t_insert(list_t *list, int status, void *data,
        void (*destroy)(void *data))
{
    list_t *new = NULL;

    if (status != 0 && status != 1) {
        return (list);
    }
    new = malloc(sizeof(list_t));
    if (new == NULL) {
        return (NULL);
    }
    new->data = data;
    new->destroy = destroy;
    list = update_link(list, new, status);
    return (list);
}
