/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** execute current shell set of commands
*/

#include "my_list.h"
#include "mysh_struct.h"
#include "mysh.h"

int execute_all(shell_t *shell)
{
    list_t *tmp = NULL;
    int status = 0;

    if (shell->command == NULL) {
        return (0);
    }
    tmp = shell->command;
    do {
        status = execute_command(shell, tmp->data);
        tmp = tmp->next;
    } while (tmp != shell->command);
    return (status);
}
