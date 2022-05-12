/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** header for builtins commands
*/

#ifndef BUILTIN_S_H_H_
    #define BUILTIN_S_H_H_

    #include "mysh_struct.h"

    #define MAX_LEN_BUILTIN_COMMAND 50
    #define NB_BUILTINS_FUNC 5

struct builtins_info_s {
    char name[MAX_LEN_BUILTIN_COMMAND];
    void (*func)(shell_t *shell, command_t *command);
};

extern const struct builtins_info_s builtins_arr[NB_BUILTINS_FUNC];

void cd_builtins(shell_t *shell, command_t *command);
void env_builtins(shell_t *shell, command_t *command);
void exit_builtins(shell_t *shell, command_t *command);
void setenv_builtins(shell_t *shell, command_t *command);
void unsetenv_builtins(shell_t *shell, command_t *command);

#endif
