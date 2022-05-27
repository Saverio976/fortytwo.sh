/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** parse char * to commands
*/

#include "my_list.h"
#include "mysh_struct.h"
#include "mysh.h"

int parse_commands(char *string, shell_t *shell)
{
    list_t_destroy(shell->command);
    string = replace_value_env(shell->env, string);
    shell->command = my_strsplit(string, ";");
    shell->command = remove_empty_commands(shell->command);
    return (0);
}
