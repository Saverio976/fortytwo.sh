/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** parse char * to commands
*/
#include "my_puts.h"
#include <stdio.h>
#include <stdlib.h>
#include "my_strings.h"
#include "my_clear_str.h"
#include "my_list.h"
#include "mysh_struct.h"
#include "mysh.h"

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

//list_t *check_alias(list_t *cm, list_t *alias)
//{
//    int test = 0;
//
//    if (cm == NULL) {
//        return (NULL);
//    }
//    if (alias == NULL) {
//        return (cm);
//    }
//    for (int i = 0; i < list_t_len(cm); i++, cm = cm->next) {
//        for (int y = 0; y < list_t_len(alias); y++, alias = alias->next) {
//        }
//    }
//    return cm;
//}

int parse_commands(char *string, shell_t *shell)
{
    list_t_destroy(shell->command);
    shell->command = my_strsplit(string, ";");
    shell->command = ampersand_separator(shell->command);
    shell->command = or_separator(shell->command);
    shell->command = remove_empty_commands(shell->command);
    //shell->command = check_alias(shell->command, shell->alias);
    return (0);
}
