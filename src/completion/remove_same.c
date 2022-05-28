/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** remove all same elements in this
*/

#include "loop.h"
#include "my_list.h"
#include "my_strings.h"

static list_t *remove_this_if_dub(list_t *elem)
{
    list_t *tmp = NULL;
    list_t *tmp_ptr = NULL;

    if (elem == NULL) {
        return (elem);
    }
    for (tmp = elem->next; tmp != elem; tmp = tmp->next) {
        if (my_strcmp(tmp->data, elem->data) != 0) {
            continue;
        }
        if (tmp->destroy != NULL) {
            tmp->destroy(tmp->data);
        }
        tmp_ptr = tmp->last;
        tmp->last->next = tmp->next;
        tmp->next->last = tmp->last;
        free_secure(tmp);
        tmp = tmp_ptr;
    }
    return (tmp);
}

list_t *remove_same(list_t *all)
{
    int len = list_t_len(all);

    for (int i = 0; i < len && all != NULL; i++, all = all->next) {
        all = remove_this_if_dub(all);
        if (all == NULL) {
            break;
        }
    }
    return (all);
}
