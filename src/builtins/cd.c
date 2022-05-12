/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** cd builtins command to change directory
*/

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "my_dico.h"
#include "my_strings.h"
#include "my_wordarray.h"
#include "builtins.h"
#include "mysh.h"
#include "mysh_struct.h"

static dico_t *set_pwd_if_not_exists(shell_t *shell, const char *tmp)
{
    dico_t *pwd = NULL;

    pwd = dico_t_get_elem(shell->env, "PWD");
    if (pwd == NULL) {
        shell->env = dico_t_add_data(shell->env, "PWD", my_strdup(tmp), free);
        pwd = dico_t_get_elem(shell->env, "PWD");
    }
    return (pwd);
}

static int set_up_pwd(shell_t *shell)
{
    char tmp[255];
    dico_t *pwd = NULL;
    dico_t *oldpwd = NULL;

    if (getcwd(tmp, 255) == NULL) {
        return (1);
    }
    pwd = set_pwd_if_not_exists(shell, tmp);
    if (pwd == NULL) {
        return (1);
    }
    oldpwd = dico_t_get_elem(shell->env, "OLDPWD");
    if (oldpwd == NULL) {
        shell->env = dico_t_add_data(shell->env, "OLDPWD", pwd->value, free);
    } else {
        free(oldpwd->value);
        oldpwd->value = pwd->value;
    }
    pwd->value = my_strdup(tmp);
    return (0);
}

static const char *get_pth_to_cd(shell_t *shell, command_t *command)
{
    char *path = NULL;
    int len = 0;

    len = my_wordarray_len(command->arguments);
    if (len > 2) {
        my_puterror("cd", "Too many arguments.\n");
        return (NULL);
    }
    if (len == 1 || my_strcmp(command->arguments[1], "~") == 0) {
        path = dico_t_get_value(shell->env, "HOME");
    } else if (my_strcmp(command->arguments[1], "-") == 0) {
        path = dico_t_get_value(shell->env, "OLDPWD");
    } else {
        path = command->arguments[1];
    }
    if (path == NULL) {
        my_puterror("", "No such file or directory.\n");
    }
    return (path);
}

void cd_builtins(shell_t *shell, command_t *command)
{
    const char *path = NULL;

    path = get_pth_to_cd(shell, command);
    if (path == NULL) {
        shell->status_code = 1;
        return;
    }
    if (chdir(path) != -1) {
        shell->status_code = set_up_pwd(shell);
    } else {
        my_puterror("cd", strerror(errno));
        write(2, ".\n", 2);
        shell->status_code = 1;
    }
}
