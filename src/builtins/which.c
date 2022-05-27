/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** exec a builtins function
*/

#include <stdbool.h>
#include <stdlib.h>
#include "builtins.h"
#include "mysh_struct.h"
#include "mysh.h"
#include "my_strings.h"
#include "my_puts.h"
#include "my_wordarray.h"

static void execute_wich(shell_t *shell, char *command)
{
    char *path = NULL;

    if (check_if_builtins(command) == true) {
        my_printf("%s: shell built-in command.\n", command);
        return;
    }
    path = get_binary_path(command, shell);
    if (path == NULL) {
        shell->status_code = 1;
    } else if (my_strcmp(path, command) != 0) {
        my_putstr(path);
        my_putstr("\n");
        return;
    }
    free(path);
}

void which_builtins(shell_t *shell, command_t *command)
{
    int nb_args = my_wordarray_len(command->arguments);
    shell->status_code = 0;

    if (nb_args < 2) {
        my_puterror("which", "Too few arguments.\n");
        shell->status_code = 1;
        return;
    }
    for (int i = 1; command->arguments[i] != NULL; i++) {
        execute_wich(shell, command->arguments[i]);
    }
}
