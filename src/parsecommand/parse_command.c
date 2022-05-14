/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** parse char * to commands
*/

#include <stdlib.h>
#include "my_clear_str.h"
#include "my_list.h"
#include "mysh_struct.h"
#include "mysh.h"

int parse_commands(char *string, shell_t *shell)
{
    char *user_input = NULL;

    list_t_destroy(shell->command);
    user_input = clear_str(string);
    shell->command = my_strsplit(user_input, ";");
    shell->command = remove_empty_commands(shell->command);
    free(user_input);
    return (0);
}
