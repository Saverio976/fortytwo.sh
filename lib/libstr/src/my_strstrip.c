/*
** EPITECH PROJECT, 2022
** LIBSTR
** File description:
** strip some char at the start and the end
*/

#include <stdlib.h>
#include "my_strings.h"

static int count_true_len(const char *str, const char *strips,
    int *start, int *stop)
{
    if (str == NULL || str[0] == '\0') {
        *start = 0;
        *stop = 0;
        return (0);
    }
    *stop = my_strlen(str) - 1;
    while (str[*start] != '\0' && my_strcontainc(strips, str[*start]) != 0) {
        (*start)++;
    }
    if (*start == *stop + 1) {
        return (0);
    }
    while (*stop > 0 && my_strcontainc(strips, str[*stop]) != 0) {
        (*stop)--;
    }
    return (*stop - *start + 1);
}

static char *fill_string(char *new, const char *str, int start, int stop)
{
    for (int i = start; i <= stop; i++) {
        new[i - start] = str[i];
    }
    new[stop - start + 1] = '\0';
    return (new);
}

char *my_strstrip(const char *str, const char *strips)
{
    char *new = NULL;
    int len = 0;
    int vect[2] = {0};

    if (str == NULL || strips == NULL || str[0] == '\0') {
        return (NULL);
    }
    len = count_true_len(str, strips, vect + 0, vect + 1);
    new = malloc(sizeof(char) * (len + 1));
    if (new == NULL) {
        return (NULL);
    }
    fill_string(new, str, vect[0], vect[1]);
    return (new);
}
