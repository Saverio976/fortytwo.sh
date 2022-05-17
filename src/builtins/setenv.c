/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** set environnement variable
*/

#include <stdlib.h>
#include "builtins.h"
#include "my_dico.h"
#include "my_strings.h"
#include "my_wordarray.h"
#include "mysh.h"
#include "mysh_struct.h"

static const char ALPHA_LETTER[] = "abcdefghijklmnopqrstuvwxyz" \
                                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

static int check_params_bad(const char *str)
{
    if (my_strcontainc(ALPHA_LETTER, str[0]) == 0) {
        my_puterror("setenv",
            "Variable name must begin with a letter.");
        return (1);
    }
    for (int i = 0; str[i] != '\0'; i++) {
        if (my_strcontainc("abcdefghijklmnopqrstuvwxyz", str[i]) == 0 &&
            my_strcontainc("ABCDEFGHIJKLMNOPQRSTUVWXYZ", str[i]) == 0 &&
            my_strcontainc("0123456789", str[i]) == 0) {
            my_puterror("setenv",
                "Variable name must contain alphanumeric characters.");
            return (1);
        }
    }
    return (0);
}

static int check_args(shell_t *shell, command_t *command, int len)
{
    if (len == 1) {
        env_builtins(shell, command);
        return (1);
    }
    if (len > 3) {
        my_puterror("setenv", "Too many arguments.\n");
        shell->status_code = 1;
        return (1);
    }
    if (check_params_bad(command->arguments[1]) == 1) {
        shell->status_code = 1;
        return (1);
    }
    return (0);
}

void setenv_builtins(shell_t *shell, command_t *command)
{
    int len = 0;
    dico_t *elem = NULL;
    char *tmp = NULL;

    len = my_wordarray_len(command->arguments);
    if (check_args(shell, command, len) == 1) {
        return;
    }
    tmp = my_strdup((len == 2) ? "" : command->arguments[2]);
    elem = dico_t_get_elem(shell->env, command->arguments[1]);
    if (elem == NULL) {
        shell->env = dico_t_add_data(shell->env, command->arguments[1],
            tmp, free);
    } else {
        free(elem->value);
        elem->value = tmp;
    }
    shell->status_code = 0;
}
