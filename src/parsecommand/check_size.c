/*
** EPITECH PROJECT, 2022
** B-PSU-210-TLS-2-1-42sh-xavier.mitault
** File description:
** env_value
*/

#include <stdio.h>
#include <stdlib.h>
#include "my_strings.h"
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

static void replace_braket(char *str)
{
    int i = 0;
    int j = 0;

    while (str[i] != '\0') {
        if (str[i] == '[') {
            i++;
            while (str[i] != ']') {
                i++;
            }
        }
        str[j] = str[i];
        i++;
        j++;
    }
    str[j] = '\0';
}

static int count_size(char *str)
{
    char *tmp = my_strdup(str);
    int size = 0;

    if (tmp == NULL)
        return (0);
    for (int i = 0; tmp[i] != '\0'; i++) {
        if (tmp[i] == '[')
            replace_braket(tmp);
    }
    size = my_strlen(tmp);
    return (size);
}

void check_size(my_files_t **files, char *str)
{
    int size = 0;
    my_files_t *tmp = (*files);
    my_files_t *tmp_delete = NULL;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '*')
            return;
    }
    size = count_size(str);
    while (tmp != NULL) {
        if (my_strlen(tmp->name) != size) {
            tmp_delete = tmp;
            tmp = tmp->next;
            delete_tmp(tmp_delete, files);
        } else {
            tmp = tmp->next;
        }
    }
}
