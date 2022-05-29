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
#include <my_strings.h>
#include "globbings.h"

int check_for_good_letters(const char *s1, const char *s2)
{
    if (*s1 == '\0') {
        if (*s2 == '*')
            return check_for_good_letters(s1, s2 + 1);
        return *s1 == *s2;
    }
    if (*s2 == '*')
        return (check_for_good_letters(s1, s2 + 1) ||
        check_for_good_letters(s1 + 1, s2));
    return (*s1 == *s2 && check_for_good_letters(s1 + 1, s2 + 1));
}

void check_letters(my_files_t **my_files, char *globbinds)
{
    my_files_t *tmp_delete = NULL;
    my_files_t *tmp = (*my_files);

    for (int i = 0; globbinds[i] != '\0'; i++) {
        if (globbinds[i] == '[' || globbinds[i] == '?')
            return;
    }
    while (tmp != NULL) {
        if (check_for_good_letters(tmp->name, globbinds) == false) {
            tmp_delete = tmp;
            tmp = tmp->next;
            delete_tmp(tmp_delete, my_files);
        } else {
            tmp = tmp->next;
        }
    }
}
