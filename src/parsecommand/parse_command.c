/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** parse char * to commands
*/

#include <stdio.h>
#include <stdlib.h>
#include "my_strings.h"
#include "my_clear_str.h"
#include "my_list.h"
#include "mysh_struct.h"
#include "my_wordarray.h"
#include "mysh.h"
#include "history.h"

list_t *or_separator(list_t *list)
{
    list_t *new = NULL;
    list_t *tmp = NULL;
    int separator = 0;

    if (list == NULL) {
        return (NULL);
    }
    for (int i = 0; i < list_t_len(list); i++, list = list->next) {
        separator = list->separator;
        tmp = my_strsplit(list->data, "||");
        if (list_t_len(tmp) != 1)
            separator = 21;
        for (int y = 0; y < list_t_len(tmp); y++, tmp = tmp->next) {
            new = list_t_add(new, separator, my_strdup(tmp->data), &free);
            separator = 2;
        }
        list_t_destroy(tmp);
    }
    list_t_destroy(list);
    return (new);
}

list_t *ampersand_separator(list_t *list)
{
    list_t *new = NULL;
    list_t *tmp = NULL;
    int separator = 0;

    if (list == NULL) {
        return (NULL);
    }
    for (int i = 0; i < list_t_len(list); i++, list = list->next) {
        separator = list->separator;
        tmp = my_strsplit(list->data, "&&");
        if (list_t_len(tmp) != 1)
            separator = 11;
        for (int y = 0; y < list_t_len(tmp); y++, tmp = tmp->next) {
            new = list_t_add(new, separator, my_strdup(tmp->data), &free);
            separator = 1;
        }
        list_t_destroy(tmp);
    }
    list_t_destroy(list);
    return (new);
}

char *my_wordarray_to_str(char **wordarray)
{
    int i = 0;
    int len = my_wordarray_size(wordarray);
    int max = my_wordarray_len(wordarray);
    char *str = my_calloc(len);

    if (wordarray == NULL || str == NULL)
        return (NULL);
    while (i < max) {
        str = my_strcat(str, wordarray[i]);
        if (i < max - 1)
            str = my_strcat(str, " ");
        i++;
    }
    return (str);
}

list_t *check_alias(list_t *cm, list_t *alias)
{
    int change = 0;
    char **tmp = NULL;

    if (cm == NULL) {
        return (NULL);
    }
    if (alias == NULL) {
        return (cm);
    }
    for (int i = 0; i < list_t_len(cm); i++, cm = cm->next) {
        change_alias(cm, alias, change, tmp);
    }
    return cm;
}

int parse_commands(char *string, shell_t *shell)
{
    char **arr = NULL;

    arr = my_wordarray_from_str(string, ' ');
    if (arr == NULL) {
        shell->status_code = 0;
        return (1);
    }
    my_wordarray_free(arr);
    list_t_destroy(shell->command);
    add_to_hist(shell->env, string);
    shell->last_input = replace_value_env(shell->env, string);
    shell->command = my_strsplit(shell->last_input, ";");
    shell->command = ampersand_separator(shell->command);
    shell->command = or_separator(shell->command);
    shell->command = remove_empty_commands(shell->command);
    shell->command = check_alias(shell->command, shell->alias);
    free(string);
    return (0);
}
