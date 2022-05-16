/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** parse char * to commands
*/

#include <stdlib.h>
#include "my_list.h"
#include "mysh_struct.h"
#include "mysh.h"

list_t *or_separator(list_t *list)
{
    list_t *new = NULL;
    list_t *tmp = list;

    if (list == NULL) {
        return (NULL);
    }
    for (int i = 0; i < list_t_len(list); i++, list = list->next) {
        tmp = my_strsplit(list->data, "||");
        for (int y = 0; y < list_t_len(tmp); y++, tmp = tmp->next) {
            new = list_t_add(new, tmp->data, &free);
        }
    }
    return (new);
}

list_t *ampersand_separator(list_t *list)
{
    list_t *new = NULL;
    list_t *tmp = list;

    if (list == NULL) {
        return (NULL);
    }
    for (int i = 0; i < list_t_len(list); i++, list = list->next) {
        tmp = my_strsplit(list->data, "&&");
        for (int y = 0; y < list_t_len(tmp); y++, tmp = tmp->next) {
            new = list_t_add(new, tmp->data, &free);
        }
    }
    return (new);
}

int parse_commands(char *string, shell_t *shell)
{
    list_t_destroy(shell->command);
    shell->command = my_strsplit(string, ";");
    shell->command = ampersand_separator(shell->command);
    shell->command = or_separator(shell->command);
    shell->command = remove_empty_commands(shell->command);
    return (0);
}
