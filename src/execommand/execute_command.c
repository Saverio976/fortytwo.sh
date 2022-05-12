/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** execute one single command
*/

#include <sys/types.h>
#include <unistd.h>
#include "my_list.h"
#include "mysh.h"
#include "mysh_struct.h"
#include "my_strings.h"

static int setup_input(command_t *cm)
{
    cm->saved_stdin = dup(0);
    if (cm->fd_input == -1 && my_strlen(cm->file_to_input) != 0) {
        cm->fd_input = open(cm->file_to_input, O_RDONLY);
        if (cm->fd_input < 0) {
            return (-1);
        }
        dup2(cm->fd_input, 0);
        close(cm->fd_input);
    } else if (cm->fd_input >= 0) {
        dup2(cm->fd_input, 0);
        close(cm->fd_input);
    } else {
        cm->fd_input = -1;
    }
    return (0);
}

int setup_redirection(command_t *cm)
{
    int ret_code = 0;

    cm->saved_stdout = dup(1);
    if (cm->fd_redirect == -1 && my_strlen(cm->redirect_to_file) != 0) {
        cm->fd_redirect = open(cm->redirect_to_file, cm->redirect_mode |
            O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        if (cm->fd_redirect < 0) {
            return (-1);
        }
        dup2(cm->fd_redirect, 1);
        close(cm->fd_redirect);
    } else if (cm->fd_redirect >= 0) {
        dup2(cm->fd_redirect, 1);
        close(cm->fd_redirect);
    } else {
        cm->fd_redirect = -1;
    }
    ret_code = setup_input(cm);
    return (ret_code);
}

int ends_redirection(command_t *cm)
{
    if (cm->saved_stdout >= 0) {
        dup2(cm->saved_stdout, 1);
    }
    if (cm->saved_stdin >= 0) {
        dup2(cm->saved_stdin, 0);
    }
    return (0);
}

int execute_command(shell_t *shell, char *string)
{
    list_t *cms = NULL;
    int status = 1;

    cms = parse_pipe(string, shell);
    if (cms == NULL) {
        return (1);
    }
    status = execute_command_parsed(shell, cms);
    list_t_destroy(cms);
    return (status);
}
