/*
** EPITECH PROJECT, 2022
** B-PSU-210-TLS-2-1-42sh-xavier.mitault
** File description:
** globbings
*/

#include <stdlib.h>
#include <stdio.h>
#include "globbings.h"

void globbing(my_files_t **my_files, char *str)
{
    check_size(my_files, str);
    if ((*my_files) == NULL)
        return;
    check_letters(my_files, str);
    check_brakets(my_files, str);
    check_interrogative(my_files, str);
}

void free_list(my_files_t *files)
{
    for (my_files_t *tmp = files; tmp != NULL; tmp = files) {
        files = files->next;
        free(tmp->name);
        free(tmp);
    }
}

static void delete_end(my_files_t *delete, my_files_t **files)
{
    my_files_t *tmp = NULL;

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

void delete_tmp(my_files_t *delete, my_files_t **files)
{
    if (delete == NULL || (*files) == NULL)
        return;
    if (delete->prev == NULL && delete->next == NULL) {
        free(delete->name);
        free(delete);
        (*files) = NULL;
        return;
    }
    delete_end(delete, files);
}
