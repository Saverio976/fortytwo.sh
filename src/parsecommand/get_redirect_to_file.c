/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** get file to input
*/

#include <stdlib.h>
#include <unistd.h>
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

static char *choose_file_redirect(char *file1, char *file2, command_t *cm)
{
    if (file1[0] == '\0') {
        free(file1);
        cm->redirect_mode = APPEND;
        return (file2);
    }
    if (file2[0] == '\0') {
        free(file2);
        cm->redirect_mode = OVERWRITE;
        return (file1);
    }
    if (my_strcmp(file1, file2) == 0) {
        free(file1);
        cm->redirect_mode = APPEND;
        return (file2);
    }
    write(2, "Ambiguous output redirect.\n", 27);
    free(file1);
    free(file2);
    return (NULL);
}

static char *get_right_file(char *string, command_t *cm)
{
    char *file1 = NULL;
    char *file2 = NULL;
    char *to_choose = NULL;

    file1 = get_right_file_single(string, ">", 3);
    file2 = get_right_file_single(string, ">>", 2);
    if (file2 == NULL || file1 == NULL) {
        if (file1 != NULL) {
            free(file1);
        }
        if (file2 != NULL) {
            free(file2);
        }
        write(2, "Ambiguous output redirect.\n", 27);
        return (NULL);
    }
    to_choose = choose_file_redirect(file1, file2, cm);
    return (to_choose);
}

char *get_redirect_to_file(char *string, int *is_error, command_t *cm)
{
    char *file = NULL;

    if (string == NULL) {
        *is_error = 1;
    }
    if (string == NULL) {
        return (NULL);
    }
    file = get_right_file(string, cm);
    if (file == NULL) {
        *is_error = 1;
    }
    cm->fd_redirect = -1;
    return (file);
}
