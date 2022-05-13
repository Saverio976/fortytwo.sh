/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** check invalid null command
*/

#include <stdbool.h>
#include <stdlib.h>
#include "mysh_struct.h"
#include "mysh.h"

bool check_null_command(list_t *pipes_str, shell_t *shell)
{
    char *tmp = NULL;

    for (int i = 0; i < list_t_len(pipes_str) && shell->status_code == 0;
            i++, pipes_str = pipes_str->next) {
        tmp = get_binary_path(pipes_str->data, shell);
        if (tmp == NULL) {
            shell->status_code = 1;
            return (false);
        }
        free(tmp);
    }
    return (true);
}
