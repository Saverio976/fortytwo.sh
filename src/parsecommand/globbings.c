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

static void globbing(my_files_t **my_files, char *str)
{
    check_size(my_files, str);
    if ((*my_files) == NULL)
        printf("No match with %s\n", str);
    check_letters(my_files, str);
    check_brakets(my_files, str);
}


char *tab_to_str2(char **tab)
{
    char *str = NULL;
    int i = 0;
    int size = 0;

    size = my_wordarray_size(tab) + my_wordarray_len(tab);
    str = my_calloc(size + 2);
    if (!str)
        return (NULL);
    while (tab[i]) {
        str = my_strcat(str, tab[i]);
        str = my_strcat(str, " ");
        i++;
    }
    return str;
}

static char *globbing_to_str(my_files_t *my_files, char *str)
{
    int size = 1;
    int index = 0;
    char **tab = NULL;

    for (my_files_t *tmp = my_files; tmp != NULL; tmp = tmp->next) {
        size += 1;
    }
    tab = malloc(sizeof(char *) * (size + 1));
    if (tab == NULL)
        return (NULL);
    for (my_files_t *tmp = my_files; tmp != NULL; tmp = tmp->next) {
        tab[index] = my_strdup(tmp->name);
        index++;
    }
    tab[index] = NULL;
    free(str);
    str = tab_to_str2(tab);
    
}

char *globbing_entry(char *str)
{
    DIR *folder = NULL;
    my_files_t *my_files = NULL;

    if (str == NULL || is_globbing(str) == false) {
        return (str);
    }
    folder = opendir("./");
    if (folder == NULL) {
        return;
    }
    struct dirent *files = NULL;
    while ((files = readdir(folder)) != NULL) {
        if (strncmp(files->d_name, ".", 1) == 0 ||
        strncmp(files->d_name, "..", 2) == 0)
            continue;
        add_files(&my_files, files->d_name);
    }
    globbing(&my_files, str);
    str = globbing_to_str(my_files, str);
    if (str[0] == '\0') {
        printf("No match\n");
    }
    return (str);
    free_list(my_files);
    closedir(folder);
}
