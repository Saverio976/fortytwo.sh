/*
** EPITECH PROJECT, 2022
** B-PSU-210-TLS-2-1-42sh-xavier.mitault
** File description:
** globbings
*/

#include <stdlib.h>
#include <stdio.h>
#include "globbings.h"

void free_list(my_files_t *files)
{
    for (my_files_t *tmp = files; tmp != NULL; tmp = files) {
        files = files->next;
        free(tmp->name);
        free(tmp);
    }
}

void delete_tmp(my_files_t *delete, my_files_t **files)
{
    my_files_t *tmp = NULL;

    if (delete == NULL || (*files) == NULL)
        return;
    if (delete->prev == NULL && delete->next == NULL) {
        free(delete->name);
        free(delete);
        (*files) = NULL;
        return;
    }
    if (delete->prev == NULL) {
        (*files) = delete->next;
        (*files)->prev = NULL;
        if ((*files)->next != NULL)
            (*files)->next->prev = (*files);
    } else {
        tmp = delete->prev;
        tmp->next = delete->next;
        if (delete->next != NULL)
            delete->next->prev = tmp;
    }
    free(delete->name);
    free(delete);
}
