/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** parse pipe redirection
*/

#include <unistd.h>
#include "my_list.h"
#include "my_strings.h"
#include "mysh.h"
#include "mysh_struct.h"

int count_tokken(char *str, const char *delim);

static void free_command_void(void *command_void)
{
    command_t *cm = command_void;

    if (cm == NULL) {
        return;
    }
    free_command(cm);
}

static int complete_two_command_p(command_t *cm_input, command_t *cm_output)
{
    int filedes[2] = {-1, -1};

    if (cm_output == NULL || cm_input == NULL ||
            my_strcmp(cm_input->file_to_input, "") != 0 ||
            my_strcmp(cm_output->redirect_to_file, "") != 0) {
        write(2, "Ambiguous output redirect.\n", 27);
        return (1);
    }
    if (pipe(filedes) == -1) {
        return (1);
    }
    cm_input->fd_input = filedes[0];
    cm_output->fd_redirect = filedes[1];
    return (0);
}

static int fill_pipes(list_t *pipes)
{
    int len = list_t_len(pipes);
    int status = 0;

    if (len == 1) {
        return (0);
    }
    for (int i = 1; i < len && pipes != NULL && pipes->next != NULL &&
            status == 0; i++, pipes = pipes->next) {
        status = complete_two_command_p(pipes->next->data, pipes->data);
    }
    return (status);
}

static list_t *add_to_parsed(list_t *list, char *data, shell_t *shell)
{
    command_t *cm = NULL;

    cm = parse_single_command(data, shell);
    if (cm == NULL) {
        list_t_destroy(list);
        shell->status_code = 1;
        return (NULL);
    }
    list = list_t_add(list, cm, free_command_void);
    return (list);
}

list_t *parse_pipe(char *input, shell_t *shell)
{
    list_t *pipes = NULL;
    list_t *piped = NULL;

    shell->status_code = 0;
    pipes = my_strsplit(input, "|");
    if (pipes == NULL || list_t_len(pipes) != count_tokken(input, "|") + 1) {
        write(2, "Invalid null command.\n", 22);
        return (NULL);
    }
    for (int i = 0; i < list_t_len(pipes) && shell->status_code == 0;
            i++, pipes = pipes->next) {
        piped = add_to_parsed(piped, pipes->data, shell);
    }
    list_t_destroy(pipes);
    if (fill_pipes(piped) != 0) {
        list_t_destroy(piped);
        return (NULL);
    }
    return (piped);
}
