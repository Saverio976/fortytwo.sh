/*
** EPITECH PROJECT, 2021
** LIBMY
** File description:
** check is str starts with str
*/

#include <stddef.h>
#include "my_strings.h"

int my_strstartswith(char const *str, char const *substr)
{
    int i = 0;
    int size = 0;

    if (str == NULL || substr == NULL) {
        return (0);
    }
    size = my_strlen(substr);
    while (str[i] != '\0' && substr[i] != '\0' && str[i] == substr[i]) {
        i++;
    }
    if (i == size) {
        return (1);
    } else {
        return (0);
    }
}
