/*
** EPITECH PROJECT, 2022
** B-PSU-210-TLS-2-1-42sh-xavier.mitault
** File description:
** globbings
*/

#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include "my_strings.h"
#include "my_wordarray.h"
#include "globbings.h"

static void add_files(my_files_t **files, char *name)
{
    my_files_t *tmp = NULL;
    my_files_t *new = malloc(sizeof(my_files_t));

    if (new == NULL)
        return;
    new->name = my_strdup(name);
    new->next = NULL;
    new->prev = NULL;
    if (new->name == NULL) {
        free(new);
    } else if ((*files) == NULL) {
        (*files) = new;
    } else {
        tmp = (*files);
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = new;
        new->prev = tmp;
    }
}

static int is_globbing(char *str)
{
    int nb_square_bracket = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '[' || str[i] == ']') {
            nb_square_bracket++;
        }
    }
    if (nb_square_bracket % 2 == 1) {
        return (false);
    }
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '*' || str[i] == '?' ||
        str[i] == '[' || str[i] == ']')
            return (true);
    }
    return (false);
}

static char *globbing_to_str(my_files_t *my_files, char *str)
{
    int size = 0;
    int index = 0;
    char **tab = NULL;

    for (my_files_t *tmp = my_files; tmp != NULL; tmp = tmp->next)
        size += 1;
    tab = malloc(sizeof(char *) * (size + 1));
    if (tab == NULL)
        return (NULL);
    for (my_files_t *tmp = my_files; tmp != NULL; tmp = tmp->next) {
        tab[index] = my_strdup(tmp->name);
        index++;
    }
    tab[index] = NULL;
    free(str);
    str = tab_to_str(tab);
    my_wordarray_free(tab);
    return (str);
}

static void globbing_loop(my_files_t **my_files, DIR *folder)
{
    struct dirent *files = NULL;

    while ((files = readdir(folder)) != NULL) {
        if ((my_strcmp(files->d_name, ".") == 0 ||
        my_strcmp(files->d_name, "..") == 0) && files->d_type == DT_DIR)
            continue;
        add_files(my_files, files->d_name);
    }
    closedir(folder);
}

char *globbing_entry(char *str)
{
    DIR *folder = NULL;
    my_files_t *my_files = NULL;

    if (str == NULL || is_globbing(str) == false)
        return (str);
    folder = opendir("./");
    if (folder == NULL)
        return (str);
    globbing_loop(&my_files, folder);
    globbing(&my_files, str);
    str = globbing_to_str(my_files, str);
    if (str[0] == '\0') {
        printf("No match\n");
    }
    free_list(my_files);
    return (str);
}
