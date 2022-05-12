/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** setup the shell and call loop
*/

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "my_dico.h"
#include "mysh.h"
#include "mysh_struct.h"

shell_t *create_shell(dico_t *env)
{
    shell_t *shell = NULL;

    shell = malloc(sizeof(shell_t));
    if (shell == NULL) {
        return (NULL);
    }
    shell->status_code = 0;
    shell->is_end = false;
    shell->last_input = NULL;
    shell->command = NULL;
    shell->env = env;
    return (shell);
}

void destroy_shell(shell_t *shell)
{
    if (shell == NULL) {
        return;
    }
    if (shell->env != NULL) {
        dico_t_destroy(shell->env);
    }
    if (shell->command != NULL) {
        list_t_destroy(shell->command);
    }
    if (shell->last_input != NULL) {
        free(shell->last_input);
    }
    free(shell);
}

int entry_point(dico_t *env)
{
    shell_t *shell = NULL;
    int ret_code = 0;

    shell = create_shell(env);
    if (shell == NULL) {
        return (84);
    }
    while (shell->is_end == false) {
        ret_code = loop(shell);
    }
    if (isatty(0) == 0) {
        ret_code = shell->status_code;
    } else {
        ret_code = (shell->status_code == 0) ? 0 : 84;
    }
    destroy_shell(shell);
    return (ret_code);
}
