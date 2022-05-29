/*
** EPITECH PROJECT, 2022
** fortytwo.sh
** File description:
** where
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include "builtins.h"
#include "my_dico.h"
#include "mysh_struct.h"
#include "mysh.h"
#include "my_fs.h"
#include "my_strings.h"
#include "my_puts.h"
#include "my_wordarray.h"
#include "loop.h"

static char **my_split_command(char *command, char *limit)
{
    int size = 1;
    int index = 0;
    char *str = NULL;
    char **tab = NULL;

    for (int nb = 0; command[nb] != '\0'; nb += 1) {
        if (command[nb] == ':')
            size += 1;
    }
    tab = malloc(sizeof(char *) * (size + 1));
    str = strtok(command, limit);
    while (str != NULL) {
        tab[index] = my_strdup(str);
        index += 1;
        str = strtok(NULL, limit);
    }
    tab[index] = NULL;
    return (tab);
}

static int print_path(char *cmd, char *path)
{
    int return_value = 1;
    char **path_array = NULL;

    path_array = my_split_command(path, ":");
    for (int i = 0; i < my_wordarray_len(path_array); i += 1) {
        path = join_path('/', 2, path_array[i], cmd);
        if (path == NULL) {
            continue;
        }
        if (access(path, X_OK) == 0) {
            printf("%s\n", path);
            return_value = 0;
        }
        free(path);
    }
    my_wordarray_free(path_array);
    return (return_value);
}

static int execute_where(shell_t *shell, char *command)
{
    char *path = NULL;
    int return_value = 1;
    int builtin_return_value = 1;

    if (check_if_builtins(command) == true) {
        my_printf("%s is a shell built-in\n", command);
        builtin_return_value = 0;
    }
    path = my_strdup(dico_t_get_value(shell->env, "PATH"));
    if (path == NULL) {
        path = my_strdup("/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin");
    }
    return_value = print_path(command, path);
    free_secure(path);
    return (return_value == 1 && builtin_return_value == 1);
}

static int make_no_sense(char *str)
{
    if (str == NULL) {
        return (false);
    }
    if (strncmp(str, "./", 2) == 0 || strncmp(str, "/", 1) == 0 ||
            strncmp(str, "../", 3) == 0) {
        return (true);
    }
    return (false);
}

void where_builtins(shell_t *shell, command_t *command)
{
    int return_value = 0;
    int nb_args = my_wordarray_len(command->arguments);
    shell->status_code = 0;

    if (nb_args < 2) {
        my_puterror("where", "Too few arguments.\n");
        shell->status_code = 1;
        return;
    }
    for (int i = 1; command->arguments[i] != NULL; i++) {
        if (make_no_sense(command->arguments[i]) == true) {
            puts("where: / in command makes no sense");
            return_value = 1;
            continue;
        }
        return_value += execute_where(shell, command->arguments[i]);
    }
    shell->status_code = (return_value >= 1) ? 1 : shell->status_code;
}
