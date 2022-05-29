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
    for (my_files_t *tmp = (*my_files); tmp != NULL; tmp = tmp->next) {
        printf("%s\n", tmp->name);
    }
}

void free_list(my_files_t *files)
{
    for (my_files_t *tmp = files; tmp != NULL; tmp = files) {
        files = files->next;
        free(tmp->name);
        free(tmp);
    }
}

void globbing_entry(char *str)
{
    DIR *folder = NULL;
    my_files_t *my_files = NULL;

    if (str == NULL || is_globbing(str) == false) {
        return;
    }
    folder = opendir("./");
    if (folder == NULL) {
        return;
    }
    struct dirent *files = NULL;
    while ((files = readdir(folder)) != NULL) {
        add_files(&my_files, files->d_name);
    }
    globbing(&my_files, str);
    //free_list(my_files);
    closedir(folder);
}
