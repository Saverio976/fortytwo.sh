/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** parse char * to commands
*/

#include <stdio.h>
#include <stdlib.h>
#include "loop.h"
#include "my_strings.h"
#include "my_clear_str.h"
#include "my_list.h"
#include "mysh_struct.h"
#include "my_wordarray.h"
#include "mysh.h"
#include "my_puts.h"
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

char *get_string_with_history(char *string, shell_t *shell)
{
    char *tmp[2] = {0};
    int nb_hist = 0;
    int max_hist = 0;

    if (string == NULL || my_strstartswith(string, "!") != 1) {
        return (string);
    }
    max_hist = inc_history_size(shell->env, 0);
    nb_hist = (my_strlen(string) == 1) ? max_hist :
        find_history_backward(shell->env, string + 1, max_hist);
    tmp[0] = get_history_line(shell->env, nb_hist);
    if (tmp[0] == NULL) {
        my_puterror(string + 1, "Event not found.\n");
    }
    tmp[1] = my_strstrip(tmp[0], "\n ");
    free_secure(string);
    free_secure(tmp[0]);
    my_printf("%s\n", (tmp[1] == NULL) ? "" : tmp[1]);
    return (tmp[1]);
}

int parse_commands(char *string, shell_t *shell)
{
    char **arr = NULL;

    shell->last_input = get_string_with_history(string, shell);
    arr = my_wordarray_from_str(shell->last_input, ' ');
    if (arr == NULL) {
        shell->status_code = 0;
        return (1);
    }
    my_wordarray_free(arr);
    list_t_destroy(shell->command);
    add_to_hist(shell->env, shell->last_input);
    arr = (char **) replace_value_env(shell->env, shell->last_input, shell);
    free_secure(shell->last_input);
    shell->last_input = (char *) arr;
    shell->command = my_strsplit(shell->last_input, ";");
    shell->command = ampersand_separator(shell->command);
    shell->command = or_separator(shell->command);
    shell->command = remove_empty_commands(shell->command);
    shell->command = check_alias(shell->command, shell->alias);
    return (0);
}
