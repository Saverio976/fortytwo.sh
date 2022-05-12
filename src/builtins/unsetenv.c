/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** unset environnement variable
*/

#include "my_dico.h"
#include "my_wordarray.h"
#include "mysh_struct.h"
#include "mysh.h"
#include "builtins.h"

void unsetenv_builtins(shell_t *shell, command_t *command)
{
    dico_t *tmp = NULL;

    if (my_wordarray_len(command->arguments) == 1) {
        my_puterror("unsetenv", "Too few arguments.\n");
        shell->status_code = 1;
        return;
    }
    for (int i = 1; command->arguments[i] != NULL; i++) {
        tmp = dico_t_get_elem(shell->env, command->arguments[i]);
        if (tmp != NULL) {
            shell->env = dico_t_rem(shell->env, command->arguments[i]);
        }
    }
    shell->status_code = 0;
}
