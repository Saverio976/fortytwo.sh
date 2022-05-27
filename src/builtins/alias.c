/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** alias builtins command
*/

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "my_dico.h"
#include "my_strings.h"
#include "my_puts.h"
#include "my_wordarray.h"
#include "builtins.h"
#include "mysh.h"
#include "mysh_struct.h"

list_t *my_alias_add(list_t *alias, char *name, char *value) {
    char *new_name = NULL;
    char *new_value = NULL;

    new_name = my_strdup(name);
    new_value = my_strdup(value);
    if (new_name == NULL || new_value == NULL) {
        return (alias);
    }
    alias = list_t_add(alias, 0, new_name, &free);
    alias = list_t_add(alias, 1, new_value, &free);
    return (alias);
}

void make_alias(shell_t *shell, char **arg)
{
    char *alias = malloc(sizeof(char) * (my_wordarray_size(arg) + 1));

    if (alias == NULL) {
        return;
    }
    alias = my_strcpy(alias, arg[2]);
    for (int i = 3; arg[i]; i++) {
        alias = my_strcat(alias, " ");
        alias = my_strcat(alias, arg[i]);
    }
    shell->alias = my_alias_add(shell->alias, arg[1], alias);
    free(alias);
}

void change_alias(list_t *cm, list_t *alias, int change, char **tmp)
{
    tmp = my_wordarray_from_str(cm->data, '\n');
    for (int y = 0; y < list_t_len(alias); y++, alias = alias->next) {
        if (alias->separator == 0 && my_strcmp(tmp[0], alias->data) == 0) {
            change = 1;
            free(tmp[0]);
            tmp[0] = my_strdup(alias->next->data);
        }
    }
    if (change == 1) {
        free(cm->data);
        cm->data = my_wordarray_to_str(tmp);
        change = 0;
    }
    my_wordarray_free(tmp);
}

void print_alias(shell_t *shell)
{
    list_t *tmp = shell->alias;

    if (tmp == NULL) {
        return;
    }
    do {
        my_putstr(tmp->data);
        my_putstr("\t");
        tmp = tmp->next;
        my_putstr(tmp->data);
        my_putchar('\n');
        tmp = tmp->next;
    } while (tmp != shell->alias);
}

void alias_builtins(shell_t *shell, command_t *command)
{
    int test = my_wordarray_len(command->arguments);
    shell->status_code = 0;

    if (test >= 3) {
        make_alias(shell, command->arguments);
        return;
    }
    if (test == 1) {
        print_alias(shell);
        return;
    }
    if (test == 0) {
        shell->status_code = 1;
        return;
    }
}
