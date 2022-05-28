/*
** EPITECH PROJECT, 2022
** fortytwo.sh
** File description:
** where
*/

#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include "builtins.h"
#include "mysh_struct.h"
#include "mysh.h"
#include "my_strings.h"
#include "my_puts.h"
#include "my_wordarray.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <string.h>

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

static void print_path(char *cmd, char *path)
{
    char **path_array = NULL;

    path_array = my_split_command(path, ":");
    for (int i = 0; path_array[i] != NULL; i += 1) {
        path = malloc(sizeof(char) * (my_strlen(path_array[i]) + my_strlen(cmd) + 2));
        if (path == NULL)
            continue;
        my_strcpy(path, path_array[i]);
        my_strcat(path, "/");
        my_strcat(path, cmd);
        if (access(path, F_OK) == 0)
            printf("%s\n", path);
        free(path);
    }
    my_wordarray_free(path_array);
}

static void execute_where(shell_t *shell, char *command)
{
    char *path = NULL;

    if (check_if_builtins(command) == true) {
        my_printf("%s is a shell built-in\n", command);
    }
    path = my_strdup(getenv("PATH"));
    if (path == NULL)
        path = my_strdup("/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin");
    print_path(command, path);
    if (path != NULL)
        free(path);
}

void where_builtins(shell_t *shell, command_t *command)
{
    int nb_args = my_wordarray_len(command->arguments);
    shell->status_code = 0;

    if (nb_args < 2) {
        my_puterror("where", "Too few arguments.\n");
        shell->status_code = 1;
        return;
    }
    for (int i = 1; command->arguments[i] != NULL; i++) {
        if (strncmp(command->arguments[i], "./", 2) == 0 ||
        strncmp(command->arguments[i], "/", 1) == 0 ||
        strncmp(command->arguments[i], "../", 3) == 0) {
            puts("where: / in command makes no sense");
            shell->status_code = 1;
            continue;
        }
        execute_where(shell, command->arguments[i]);
    }
}
