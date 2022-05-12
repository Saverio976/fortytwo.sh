/*
** EPITECH PROJECT, 2022
** LIBLIST
** File description:
** destroy all linked list
*/

#include <stdlib.h>
#include "my_list.h"

int list_t_destroy(list_t *dico)
{
    list_t *tmp = NULL;
    list_t *cursor = NULL;
    int nb = 0;

    if (dico == NULL) {
        return (0);
    }
    cursor = dico;
    do {
        tmp = cursor->next;
        cursor->destroy(cursor->data);
        free(cursor);
        cursor = tmp;
        nb += 1;
    } while (cursor != dico && cursor != NULL);
    return (nb);
}
