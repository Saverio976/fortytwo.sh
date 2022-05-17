/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** loop until the end
*/

#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "my_strings.h"
#include "my_dico.h"
#include "mysh_struct.h"
#include "mysh.h"

static int end_loop(int ret_code, shell_t *shell)
{
    if (shell->last_input != NULL) {
        free(shell->last_input);
    }
    shell->last_input = NULL;
    shell->last_input_len = 0;
    shell->status_code = ret_code;
    if (shell->almost_the_end == true) {
        shell->is_end = true;
    }
    return (ret_code);
}

int loop(shell_t *shell)
{
    int status = 0;

    if (isatty(0)) {
        print_prompt(shell);
    }
    if (getline(&shell->last_input, &shell->last_input_len, stdin) <= 0) {
        shell->is_end = true;
        return (end_loop(shell->status_code, shell));
    }
    shell->last_input[my_strlen(shell->last_input) - 1] = '\0';
    if (parse_commands(shell->last_input, shell) != 0) {
        return (end_loop(shell->status_code, shell));
    }
    status = execute_all(shell);
    return (end_loop(status, shell));
}
