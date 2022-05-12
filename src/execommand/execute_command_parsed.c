/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** execute parsed command
*/

#include <sys/wait.h>
#include <stdbool.h>
#include <unistd.h>
#include "my_list.h"
#include "mysh_struct.h"
#include "mysh.h"

static int execute_child_genitor(list_t *cms, shell_t *shell, int i)
{
    int new_pid = 0;
    int status = 0;
    int is_in_fork = true;

    if (list_t_len(cms) == i + 1 &&
            check_if_builtins(((command_t *) cms->data)->binary)) {
        is_in_fork = false;
    } else {
        new_pid = fork();
    }
    ((command_t *) cms->data)->pid_child = new_pid;
    if (new_pid == 0) {
        status = execute_command_child(cms->data, shell, is_in_fork);
    } else {
        status = 1;
    }
    return (status);
}

static int count_valid(list_t *cms)
{
    int nb = 0;

    for (int i = 0; i < list_t_len(cms); i++, cms = cms->next) {
        if (((command_t *) cms->data)->pid_child != -1) {
            nb++;
        }
    }
    return (nb);
}

static int wait_until_end(list_t *cms, list_t *last, shell_t *shell)
{
    command_t *cm = NULL;
    int wstatus = 0;
    int status = shell->status_code;
    int need_terminate = 0;

    for (; count_valid(cms) > 0 && need_terminate == 0 &&
            shell->is_end == false; cms = cms->next) {
        cm = cms->data;
        if (cm->pid_child == -1) {
            continue;
        }
        if (cm->pid_child == 0 ||
                waitpid(cm->pid_child, &wstatus, WNOHANG) != 0) {
            wstatus = kill_inferior_commands(shell, wstatus, cms, last);
            cm->pid_child = -1;
            status = (cms == last) ? wstatus : status;
            need_terminate = (cms == last) ? 1 : 0;
        }
    }
    return (status);
}

int execute_command_parsed(shell_t *shell, list_t *cms)
{
    int status = 0;
    list_t *last = NULL;

    if (shell == NULL || cms == NULL) {
        return (1);
    }
    last = cms->last;
    for (int i = 0; i < list_t_len(cms) && shell->is_end == false;
            i++, cms = cms->next) {
        setup_redirection(cms->data);
        execute_child_genitor(cms, shell, i);
        ends_redirection(cms->data);
    }
    status = wait_until_end(cms, last, shell);
    return (status);
}
