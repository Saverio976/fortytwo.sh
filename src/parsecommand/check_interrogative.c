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
#include "my_strings.h"

static int check_if_good(char *file, char *globbinds)
{
    char *compare = my_strdup(globbinds);

    if (compare == NULL)
        return (true);
    for (int i = 0; globbinds[i] != '\0'; i ++) {
        if (globbinds[i] != '?')
            continue;
        compare[i] = file[i];
    }
    if (check_for_good_letters(file, compare) == true) {
        free(compare);
        return (false);
    }
    free(compare);
    return (true);
}

void check_interrogative(my_files_t **my_files, char *globbinds)
{
    my_files_t *tmp_delete = NULL;
    my_files_t *tmp = (*my_files);

    for (int i = 0; globbinds[i] != '\0'; i ++) {
        if (globbinds[i] == '*' || globbinds[i] == '[')
            return;
    }
    while (tmp != NULL) {
        if (check_if_good(tmp->name, globbinds) == true) {
            tmp_delete = tmp;
            tmp = tmp->next;
            delete_tmp(tmp_delete, my_files);
        } else {
            tmp = tmp->next;
        }
    }
}
