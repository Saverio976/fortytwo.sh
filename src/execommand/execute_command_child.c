/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** execute a command as a child process
*/

#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "my_wordarray.h"
#include "mysh_struct.h"
#include "mysh.h"

static int exec_builtin_cmd(command_t *cm, shell_t *shell, bool is_fork)
{
    int status = 0;

    status = exec_builtins(shell, cm);
    if (is_fork == false) {
        return (status);
    }
    free_command(cm);
    destroy_shell(shell);
    exit(status);
}

int execute_command_child(command_t *cm, shell_t *shell, bool is_fork)
{
    char **env = NULL;

    if (check_if_builtins(cm->binary)) {
        return (exec_builtin_cmd(cm, shell, is_fork));
    }
    env = get_env_from_dico(shell->env);
    if (env != NULL) {
        execve(cm->binary, cm->arguments, env);
    }
    if (env != NULL) {
        my_wordarray_free(env);
    }
    free_command(cm);
    destroy_shell(shell);
    exit(-1);
}
