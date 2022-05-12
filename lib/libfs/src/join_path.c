/*
** EPITECH PROJECT, 2022
** LIBFS
** File description:
** join a number of path with a delim
*/

#include <stdarg.h>
#include <stdlib.h>
#include "my_strings.h"

static int get_len_str_total(va_list ap, int nb_path)
{
    int len = 0;
    const char *tmp = NULL;

    for (int i = 0; i < nb_path; i++) {
        tmp = va_arg(ap, const char *);
        if (tmp == NULL) {
            continue;
        }
        len += my_strlen(tmp);
    }
    return (len);
}

static int fill_char_with_delim(const char *str, int index,
        char *new)
{
    for (int j = 0; str[j] != '\0'; j++) {
        new[index] = str[j];
        index += 1;
    }
    return (index);
}

static char *create_new_path(char delim, int nb_path, va_list ap, int len)
{
    char *new = NULL;
    const char *tmp = NULL;
    int index = 0;

    new = malloc(sizeof(char) * (len + 1 + nb_path - 1));
    if (new == NULL) {
        return (NULL);
    }
    for (int i = 0; i < nb_path; i++) {
        tmp = va_arg(ap, const char *);
        if (tmp == NULL) {
            continue;
        }
        index = fill_char_with_delim(tmp, index, new);
        if (index <= len) {
            new[index++] = delim;
        }
    }
    new[len + nb_path - 1] = '\0';
    return (new);
}

char *join_path(char delim, int nb_path, ...)
{
    va_list ap;
    va_list cpy;
    int len = 0;
    char *new = NULL;

    va_start(ap, nb_path);
    va_copy(cpy, ap);
    len = get_len_str_total(cpy, nb_path);
    va_end(cpy);
    new = create_new_path(delim, nb_path, ap, len);
    va_end(ap);
    return (new);
}
