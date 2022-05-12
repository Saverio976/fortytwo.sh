/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** execute command buf in the parent of the for
*/

#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "my_strings.h"
#include "mysh_struct.h"
#include "mysh.h"

static void print_right_error(shell_t *shell, command_t *cm, int wstatus)
{
    char *tmp = NULL;

    if (shell->status_code == -1 || shell->status_code == 255) {
        my_puterror(cm->arguments[0], "Command not found.\n");
        shell->status_code = 1;
        return;
    }
    if (shell->status_code - 128 <= 0) {
        return;
    }
    tmp = strsignal(shell->status_code - 128);
    write(2, tmp, my_strlen(tmp));
    if (WIFSIGNALED(wstatus) && WCOREDUMP(wstatus)) {
        write(2, " (core dumped)", 14);
    }
    write(2, "\n", 1);
}

static int print_right_status(shell_t *shell, int wstatus, command_t *cm)
{
    if (cm->pid_child == -1 || check_if_builtins(cm->binary) != 0) {
        return (shell->status_code);
    }
    shell->status_code = -1;
    if (shell->status_code == -1 && WIFEXITED(wstatus)) {
        shell->status_code = WEXITSTATUS(wstatus);
    }
    if (shell->status_code == -1 && WIFSIGNALED(wstatus)) {
        shell->status_code = WTERMSIG(wstatus) + 128;
    }
    if (shell->status_code == -1 && WIFSTOPPED(wstatus)) {
        shell->status_code = WSTOPSIG(wstatus) + 128;
    }
    print_right_error(shell, cm, wstatus);
    return (shell->status_code);
}

int kill_inferior_commands(shell_t *shell, int wstatus, list_t *cms,
    list_t *last)
{
    pid_t pid = 0;
    command_t *cm = NULL;

    if (shell == NULL || cms == NULL || last == NULL) {
        return (84);
    }
    wstatus = print_right_status(shell, wstatus, cms->data);
    for (; cms != last; cms = cms->last) {
        cm = cms->data;
        pid = cm->pid_child;
        if (pid != -1 && pid != 0) {
            cm->pid_child = -1;
            kill(pid, SIGQUIT);
        }
    }
    return (wstatus);
}

int execute_command_genitor(pid_t pid_child, command_t *cm, shell_t *shell)
{
    int wstatus = -1;
    int w = 0;

    w = waitpid(pid_child, &wstatus, 0);
    if (w == -1) {
        return (1);
    }
    wstatus = print_right_status(shell, wstatus, cm);
    return (wstatus);
}
