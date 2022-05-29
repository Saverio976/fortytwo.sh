/*
** EPITECH PROJECT, 2022
** B-PSU-210-TLS-2-1-42sh-xavier.mitault
** File description:
** globbings
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "globbings.h"

static void delete_tmp(my_files_t *delete, my_files_t **files)
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

static char *replace_begin(char *globbinds, char *file, char letter)
{
    int i = 0;
    char *new = malloc(sizeof(char) * (my_strlen(globbinds) +
    my_strlen(file) + 1));

    if (globbinds == NULL || file == NULL || new == NULL)
        return (NULL);
    for (i = 0; file[i] != '\0'; i++) {
        if (file[i] == letter) {
            break;
        }
        new[i] = file[i];
    }
    new[i] = '\0';
    new = strcat(new, &globbinds[1]);
    return (new);
}

static char *replace_end(char *globbinds, char *file, char letter)
{
    int i = 0;
    char *new = malloc(sizeof(char) * (my_strlen(globbinds) +
    my_strlen(file) + 1));

    if (globbinds == NULL || file == NULL || new == NULL)
        return (NULL);
    for (i = 0; globbinds[i] != '\0'; i++) {
        new[i] = globbinds[i];
        if (globbinds[i] == letter) {
            break;
        }
    }
    new[i + 1] = '\0';
    for (i = my_strlen(file) - 1; i >= 0; i--) {
        if (file[i] == letter) {
            i += 1;
            break;
        }
    }
    new = strcat(new, &file[i]);
    return (new);
}

int check_for_good_letters(char *str, char *globbinds)
{
    char *new = NULL;
    char *new2 = NULL;
    int size = my_strlen(globbinds);

    if (size < 2)
        return (true);
    if (globbinds[0] == '*') {
        new = replace_begin(globbinds, str, globbinds[1]);
    } else if (globbinds[size - 1] == '*') {
        new = replace_end(globbinds, str, globbinds[size - 2]);
    }
    if (strcmp(new, str) == 0) {
        return (false);
    }
    return (true);
}

void check_letters(my_files_t **my_files, char *globbinds)
{
    my_files_t *tmp_delete = NULL;
    my_files_t *tmp = (*my_files);

    while (tmp != NULL) {
        if (check_for_good_letters(tmp->name, globbinds) == true) {
            tmp_delete = tmp;
            tmp = tmp->next;
            delete_tmp(tmp_delete, my_files);
        } else {
            tmp = tmp->next;
        }
    }
}
