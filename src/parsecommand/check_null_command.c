/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** check invalid null command
*/

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "my_list.h"
#include "my_strings.h"
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
        if (my_strcmp(tmp, "") == 0) {
            shell->status_code = 1;
            free(tmp);
            write(2, "Invalid null command.\n", 22);
            return (false);
        }
        free(tmp);
    }
    return (true);
}

bool check_missing_name(list_t *pipes_str, shell_t *shell)
{
    command_t cm = {0};
    char *tmp = NULL;

    for (int i = 0; i < list_t_len(pipes_str) && shell->status_code == 0;
            i++, pipes_str = pipes_str->next) {
        tmp = get_file_to_input(pipes_str->data, &shell->status_code, &cm);
        if (tmp == NULL) {
            return (false);
        }
        free(tmp);
        tmp = get_redirect_to_file(pipes_str->data, &shell->status_code, &cm);
        if (tmp == NULL) {
            return (false);
        }
    }
    return (true);
}
