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

static int find_pos(char *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] == '[')
            return (i);
        i++;
    }
    return (0);
}

static char *create_compare_string(char *str)
{
    int str_index = 0;
    int is_ok = true;
    char *new = malloc(sizeof(char) * (strlen(str) + 1));

    if (new == NULL)
        return (NULL);
    for (int i = 0; str[i] != '\0'; i ++) {
        if (str[i] == '[')
            is_ok = false;
        if (str[i] == ']')
            is_ok = true;
        if (is_ok == true) {
            new[str_index] = str[i];
            str_index++;
        }
    }
    new[str_index] = '\0';
    return (new);
}

static char find_end(char *str, int pos)
{
    char c = 'a';

    for (int i = pos; str[i] != '\0'; i++) {
        if (str[i] == ']' && i >= 1)
            return (str[i - 1]);
    }
    return (c);
}

static int check_for_brakets(char *file, char *globbinds)
{
    char start = 'a';
    char end = 'z';
    int pos = 0;
    char *compare = NULL;

    pos = find_pos(globbinds);
    compare = create_compare_string(globbinds);
    start = globbinds[pos + 1];
    end = find_end(globbinds, pos);
    for (int i = start; i <= end; i ++) {
        compare[pos] = i;
        if (check_for_good_letters(file, compare) == true) {
            free(compare);
            return (false);
        }
    }
    free(compare);
    return (true);
}

void check_brakets(my_files_t **my_files, char *globbinds)
{
    my_files_t *tmp_delete = NULL;
    my_files_t *tmp = (*my_files);

    for (int i = 0; globbinds[i] != '\0'; i ++) {
        if (globbinds[i] == '?')
            return;
    }
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
