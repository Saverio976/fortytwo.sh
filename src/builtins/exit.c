/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** exit the shell
*/

#include "builtins.h"
#include "my_wordarray.h"
#include "my_conversions.h"
#include "mysh_struct.h"
#include "mysh.h"
#include <stdbool.h>

void exit_builtins(shell_t *shell, command_t *command)
{
    int len = 0;
    int nbr = 0;
    int is_error = 0;

    len = my_wordarray_len(command->arguments);
    if (len != 1 && len != 2) {
        shell->status_code = 1;
        my_puterror("exit", "Expression Syntax.\n");
        return;
    }
    if (len == 2) {
        nbr = my_getnbri(command->arguments[1], &is_error);
        if (is_error != 0 || command->arguments[1][0] == '+') {
            shell->status_code = 1;
            my_puterror("exit", "Expression Syntax.\n");
            return;
        }
    }
    shell->status_code = nbr;
    shell->is_end = true;
}
