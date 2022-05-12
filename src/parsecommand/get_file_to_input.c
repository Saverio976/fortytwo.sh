/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** get file to input
*/

#include <stdlib.h>
#include "my_list.h"
#include "my_strings.h"
#include "mysh.h"
#include "mysh_struct.h"

static char *get_file_from_list(list_t *list)
{
    list_t *words = NULL;
    char *string = NULL;
    char *file = NULL;

    if (list_t_len(list) != 2) {
        return (NULL);
    }
    string = list->next->data;
    words = my_strsplit(string, " ");
    if (words == NULL || list_t_len(words) < 1) {
        list_t_destroy(words);
        return (NULL);
    }
    file = my_strdup(words->data);
    return (file);
}

static char *get_right_file_single(char *string, const char *delim, int nb_max)
{
    list_t *list = NULL;
    char *file = NULL;

    list = my_strsplit(string, delim);
    if (list_t_len(list) <= 0 || list_t_len(list) > nb_max) {
        return (NULL);
    }
    if (list_t_len(list) == 2) {
        file = get_file_from_list(list);
    } else {
        file = malloc(sizeof(char) * 1);
        file[0] = '\0';
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
static char *get_right_file(char *string)
{
    char *file = NULL;

    file = get_right_file_single(string, "<", 2);
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
    }
    if (string == NULL) {
        return (NULL);
    }
    file = get_right_file(string);
    cm->fd_input = -1;
    return (file);
}
