/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** get arguments array of the command
*/

#include <stdbool.h>
#include <stdlib.h>
#include "my_strings.h"
#include "my_list.h"
#include "mysh.h"

static bool is_ok_count(const char *str)
{
    if (str == NULL) {
        return (false);
    }
    if (str[0] == '>' &&
            (my_strcmp(str, ">") == 0 || my_strcmp(str, ">>") == 0)) {
        return (false);
    }
    if (str[0] == '<' &&
            (my_strcmp(str, "<") == 0 || my_strcmp(str, "<<") == 0)) {
        return (false);
    }
    return (true);
}

static int get_len(list_t *list)
{
    int len = 0;
    int true_len = 0;

    len = list_t_len(list);
    for (int i = 0; i < len; i++, list = list->next) {
        if (is_ok_count(list->data) == true) {
            true_len++;
        } else {
            true_len--;
        }
    }
    return (true_len);
}

static char **create_array_list(list_t *list, int len)
{
    char **arr = NULL;

    arr = malloc(sizeof(char *) * (len + 1));
    if (arr == NULL) {
        return (NULL);
    }
    arr[len] = NULL;
    for (int i = 0; i < len; list = list->next) {
        if (is_ok_count(list->data) == false) {
            list = list->next;
        }
        arr[i] = my_strdup(list->data);
        i++;
    }
    return (arr);
}

char **get_arguments_array(char *input)
{
    list_t *list_args = NULL;
    int len = 0;
    char **arr = NULL;

    list_args = my_strsplit(input, " ");
    if (list_args == NULL) {
        return (NULL);
    }
    len = get_len(list_args);
    if (len <= 0) {
        list_t_destroy(list_args);
        return (NULL);
    }
    arr = create_array_list(list_args, len);
    list_t_destroy(list_args);
    return (arr);
}
