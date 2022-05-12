/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** get binary from string
*/

#include <unistd.h>
#include <stdlib.h>
#include "my_list.h"
#include "my_dico.h"
#include "my_puts.h"
#include "my_strings.h"
#include "my_fs.h"
#include "mysh.h"
#include "mysh_struct.h"

static char *iterr_all_path(list_t *path_list, const char *string)
{
    char *true_path = NULL;
    list_t *tmp = path_list;

    do {
        true_path = join_path('/', 2, tmp->data, string);
        if (true_path == NULL) {
            return (NULL);
        }
        if (access(true_path, X_OK) == 0) {
            return (true_path);
        }
        free(true_path);
        tmp = tmp->next;
    } while (tmp != path_list);
    if (access(string, X_OK) == 0) {
        return (my_strdup(string));
    }
    return (NULL);
}

static char *get_binary_from_path(const char *string, shell_t *shell)
{
    list_t *pathss = NULL;
    char *path = NULL;
    char *binary = NULL;
    char def_path[] = "/usr/local/bin:/usr/bin:/bin:/usr/local/sbin";

    path = dico_t_get_value(shell->env, "PATH");
    if (path == NULL) {
        path = def_path;
    }
    pathss = my_strsplit(path, ":");
    if (pathss == NULL) {
        return (NULL);
    }
    binary = iterr_all_path(pathss, string);
    list_t_destroy(pathss);
    return (binary);
}

static char *get_binary_path_str(const char *string, shell_t *shell)
{
    char *binary = NULL;

    if (string == NULL) {
        return (NULL);
    }
    if (my_strstartswith(string, "./") || check_if_builtins(string)) {
        return (my_strdup(string));
    }
    binary = get_binary_from_path(string, shell);
    return (binary);
}

char *get_binary_path(char *string, shell_t *shell)
{
    list_t *list = NULL;
    char *binary = NULL;

    if (string == NULL) {
        return (NULL);
    }
    list = my_strsplit(string, " ");
    if (list == NULL) {
        return (NULL);
    }
    binary = get_binary_path_str(list->data, shell);
    if (binary == NULL) {
        my_puterror(list->data, "Command not found.\n");
    }
    list_t_destroy(list);
    return (binary);
}
