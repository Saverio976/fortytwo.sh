/*
** EPITECH PROJECT, 2022
** LIBLIST
** File description:
** get len of list
*/

#include "my_list.h"

int list_t_len(list_t *list)
{
    int i = 0;
    list_t *tmp = NULL;

    if (list == NULL) {
        return (-1);
    }
    tmp = list;
    do {
        i++;
        tmp = tmp->next;
    } while (tmp != list);
    return (i);
}
