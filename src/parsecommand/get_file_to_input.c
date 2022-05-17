/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** get file to input
*/

#include <stdlib.h>
#include <unistd.h>
#include "macros.h"
#include "my_list.h"
#include "my_strings.h"
#include "mysh.h"
#include "mysh_struct.h"

static char *get_file_from_list(list_t *list, int *is_error)
{
    list_t *words = NULL;
    char *string = NULL;
    char *file = NULL;

    string = list->next->data;
    words = my_strsplit(string, " ");
    if (words == NULL || list_t_len(words) < 1 ||
            my_strstartswith(words->data, ">")) {
        write(2, "Missing name for redirect.", 26);
        list_t_destroy(words);
        *is_error = 1;
        return (NULL);
    }
    file = my_strdup(words->data);
    if (file == NULL) {
        write(2, "Missing name for redirect.", 26);
    }
    return (file);
}

static char *get_right_file_single(char *string, const char *delim, int nb_max,
    int *is_error)
{
    list_t *list = NULL;
    char *file = NULL;

    list = my_strsplit(string, delim);
    if (list_t_len(list) <= 0 || list_t_len(list) > nb_max) {
        *is_error = 1;
        write(2, (list == NULL) ? MISSING_ERR : AMBIGUOUS_IN_ERR,
            (list == NULL) ? 27 : 26);
        return (NULL);
    }
    if (list_t_len(list) == 2) {
        file = get_file_from_list(list, is_error);
    } else {
        file = my_calloc(1);
    }
    list_t_destroy(list);
    return (file);
}

//file = get_right_file_single(string, ">");
//if (file != NULL && file[0] != '\0') {
//    return (file);
//}
//if (file[0] == '\0') {
//    free(file);
//}
static char *get_right_file(char *string, int *is_error)
{
    char *file = NULL;

    if (my_strcmp(string, "<<") == 0 || my_strcmp(string, "<") == 0) {
        write(2, MISSING_ERR, 27);
        *is_error = 1;
        return (NULL);
    }
    file = get_right_file_single(string, "<<", 2, is_error);
    if (*is_error == 1) {
        if (file != NULL) {
            free(file);
        }
        return (NULL);
    }
    free(file);
    file = get_right_file_single(string, "<", 2, is_error);
    if (file != NULL) {
        return (file);
    }
    return (NULL);
}

char *get_file_to_input(char *string, int *is_error, command_t *cm)
{
    char *file = NULL;

    if (string == NULL) {
        *is_error = 1;
        return (NULL);
    }
    file = get_right_file(string, is_error);
    if (file == NULL) {
        *is_error = 1;
    }
    cm->fd_input = -1;
    return (file);
}
