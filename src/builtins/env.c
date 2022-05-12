/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** show env
*/

#include "builtins.h"
#include "my_dico.h"
#include "my_strings.h"
#include "my_puts.h"
#include "mysh.h"
#include "mysh_struct.h"

void env_builtins(shell_t *shell, __attribute__((unused)) command_t *command)
{
    dico_t *tmp = NULL;

    shell->status_code = 0;
    if (shell->env == NULL) {
        return;
    }
    tmp = shell->env;
    do {
        if (my_strlen(tmp->value) <= 0) {
            my_printf("%s=\n", tmp->key);
        } else {
            my_printf("%s=%s\n", tmp->key, tmp->value);
        }
        tmp = tmp->next;
    } while (tmp != shell->env);
}
