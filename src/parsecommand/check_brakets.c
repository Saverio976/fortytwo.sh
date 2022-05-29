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

static int find_pos(char *str)
{
    int pos = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '[') {
            pos = i + 1;
            break;
        }
    }
    return (pos);
}

static int check_char(char *str, char letter)
{
    int i = 0;

    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == letter)
            return (true);
    }
    return (false);
}

int check_for_brakets(char *file, char *globbinds)
{
    char c = '\0';
    int pos = 0;

    if (file == NULL || globbinds == NULL)
        return (true);
    for (int i = 0; globbinds[i] != '\0'; i++) {
        if (globbinds[i] == '*' || globbinds[i] == '?')
            return (false);
    }
    pos = find_pos(globbinds);
    c = file[pos - 1];
    if (check_char(globbinds, c) == true)
        return (false);
    return (true);
}

void check_brakets(my_files_t **my_files, char *globbinds)
{
    my_files_t *tmp_delete = NULL;
    my_files_t *tmp = (*my_files);

    while (tmp != NULL) {
        if (check_for_brakets(tmp->name, globbinds) == true) {
            tmp_delete = tmp;
            tmp = tmp->next;
            delete_tmp(tmp_delete, my_files);
        } else {
            tmp = tmp->next;
        }
    }
}
