/*
** EPITECH PROJECT, 2022
** LIBSTR
** File description:
** insert char to position in str
*/

#include <stddef.h>
#include <stdlib.h>
#include "my_strings.h"

char *my_strinsert(char *str, char c, int index)
{
    char *tmp = NULL;

    if (str == NULL || index > my_strlen(str) + 1) {
        return (NULL);
    }
    tmp = my_strdup(str + index);
    if (tmp == NULL) {
        return (NULL);
    }
    my_strcpy(str + index + 1, tmp);
    free(tmp);
    str[index] = c;
    return (str);
}

char *my_strreminsert(char *str, int index)
{
    if (str == NULL || index > my_strlen(str)) {
        return (NULL);
    }
    for (int i = index; str[i + 1] != '\0'; i++) {
        str[i] = str[i + 1];
    }
    str[my_strlen(str) - 1] = '\0';
    return (str);
}
