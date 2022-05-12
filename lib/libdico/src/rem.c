/*
** EPITECH PROJECT, 2022
** LIBLIST
** File description:
** remove elem from list
*/

#include <stdlib.h>
#include "my_dico.h"

static dico_t *get_return_rem(dico_t *dico, dico_t *elem)
{
    dico_t *ret = NULL;

    if (elem == dico) {
        ret = dico->next;
    } else {
        ret = dico;
    }
    if (elem->last == elem->next && elem == elem->last) {
        ret = NULL;
    }
    return (ret);
}

dico_t *dico_t_rem(dico_t *dico, char const *key)
{
    dico_t *elem = dico_t_get_elem(dico, key);
    dico_t *tmp = NULL;

    if (elem == NULL) {
        return (dico);
    }
    if (elem->last != NULL) {
        elem->last->next = elem->next;
    }
    if (elem->next != NULL) {
        elem->next->last = elem->last;
    }
    tmp = get_return_rem(dico, elem);
    if (elem->destroy != NULL) {
        elem->destroy(elem->value);
    }
    free(elem);
    return (tmp);
}

dico_t *dico_t_rem_ptr(dico_t *dico, void *ptr)
{
    if (dico == NULL) {
        return (NULL);
    }
    for (dico_t *tmp = dico->next; tmp != dico; tmp = tmp->next) {
        if (tmp->value == ptr) {
            return (dico_t_rem(dico, tmp->key));
        }
    }
    return (dico);
}
