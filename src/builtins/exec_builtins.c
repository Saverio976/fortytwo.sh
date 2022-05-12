/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** exec a builtins function
*/

#include "my_strings.h"
#include "mysh_struct.h"
#include "mysh.h"
#include "builtins.h"

int exec_builtins(shell_t *shell, command_t *command)
{
    shell->status_code = -1;

    for (int i = 0; i < NB_BUILTINS_FUNC; i++) {
        if (my_strcmp(command->binary, builtins_arr[i].name) == 0) {
            builtins_arr[i].func(shell, command);
            return (shell->status_code);
        }
    }
    return (shell->status_code);
}
