/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** complete with the string given
*/

#include <stdbool.h>
#include <stddef.h>
#include <dirent.h>
#include <unistd.h>
#include "my_dico.h"
#include "my_fs.h"
#include "my_list.h"
#include "my_strings.h"
#include "my_wordarray.h"
#include "loop.h"
#include "complete.h"
#include "my_macro.h"

list_t *get_all_exe_in(const char *path, bool is_exec)
{
    DIR *dir = NULL;
    list_t *list = NULL;
    struct dirent *name = NULL;
    char *tmp = NULL;

    dir = opendir(path);
    if (dir == NULL) {
        return (NULL);
    }
    for (name = readdir(dir); name != NULL; name = readdir(dir)) {
        tmp = join_path('/', 2, path, name->d_name);
        if (tmp != NULL && (is_exec == false || access(tmp, X_OK) == 0)) {
            list = list_t_add(list, 0, my_strdup(name->d_name), free_secure);
        }
        free_secure(tmp);
    }
    closedir(dir);
    return (list);
}

list_t *get_all_exe_startswith(list_t *all, const char *path, char *string,
    bool is_exec)
{
    list_t *list = NULL;

    list = get_all_exe_in(path, is_exec);
    for (int i = 0; i < list_t_len(list); i++, list = list->next) {
        if (my_strstartswith(list->data, string) == 1) {
            all = list_t_add(all, 0, my_strdup(list->data), free_secure);
        }
    }
    list_t_destroy(list);
    return (all);
}

list_t *complete_path(char *string, __attribute__((unused)) dico_t *env,
    bool add_point)
{
    char path[] = ".";
    list_t *all = NULL;
    char *tmp = NULL;

    all = get_all_exe_startswith(all, path, string, add_point);
    if (add_point == false) {
        return (all);
    }
    for (int i = 0; i < list_t_len(all); i++, all = all->next) {
        tmp = join_path('/', 2, ".", all->data);
        if (tmp != NULL) {
            all->destroy(all->data);
            all->data = tmp;
        }
    }
    return (all);
}

list_t *complete_exe(char *string, dico_t *env)
{
    char *path = dico_t_get_value(env, "PATH");
    char def_path[] = "/usr/local/bin:/usr/bin:/bin:/usr/local/sbin";
    char **arr = NULL;
    list_t *all = NULL;

    if (my_strstartswith(string, "./") == 1) {
        return (complete_path(string + 2, env, true));
    }
    path = (path == NULL) ? def_path : path;
    arr = my_wordarray_from_str(path, ':');
    if (arr == NULL) {
        return (NULL);
    }
    for (int i = 0; arr[i] != NULL; i++) {
        all = get_all_exe_startswith(all, arr[i], string, true);
    }
    my_wordarray_free(arr);
    return (all);
}

list_t *complete_this(char *string, dico_t *env)
{
    char **arr = NULL;
    list_t *ret = NULL;

    arr = my_wordarray_from_str(string, ' ');
    if (arr == NULL) {
        return (NULL);
    }
    if (my_wordarray_len(arr) == 1) {
        ret = complete_exe(arr[0], env);
    } else {
        ret = complete_path(arr[MAX(my_wordarray_len(arr) - 1, 0)], env, false);
    }
    ret = remove_same(ret);
    my_wordarray_free(arr);
    return (ret);
}
