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
    alias = list_t_add(alias, 0, new_name, &free);
    alias = list_t_add(alias, 1, new_value, &free);
    return (alias);
}

void make_alias(shell_t *shell, char **arg)
{
    char *alias = my_strdup(arg[2]);

    for (int i = 3; arg[i]; i++) {
        alias = my_strcat(alias, " \0");
        alias = my_strcat(alias, arg[i]);
    }
    shell->alias = my_alias_add(shell->alias, arg[1], alias);
    free(alias);
}

void print_alias(shell_t *shell)
{
    list_t *tmp = shell->alias;

    if (tmp == NULL) {
        my_putstr("alias: no alias defined.\n");
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
        my_putstr("alias error");
        shell->status_code = 1;
        return;
    }
}
