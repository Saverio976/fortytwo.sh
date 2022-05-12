/*
** EPITECH PROJECT, 2021
** LIBMY
** File description:
** dup a str
*/

#include <stdlib.h>
#include "my_strings.h"

char *my_strdup(char const *str)
{
    int size = 0;
    char *new = NULL;

    if (str == NULL) {
        return (NULL);
    }
    size = my_strlen(str);
    new = malloc(sizeof(char) * (size + 1));
    if (new == NULL) {
        return (NULL);
    }
    for (int i = 0; i < size; i++) {
        new[i] = str[i];
    }
    new[size] = '\0';
    return (new);
}
