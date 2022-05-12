/*
** EPITECH PROJECT, 2021
** LIBMY
** File description:
** reverse a str
*/

#include <stddef.h>
#include "my_strings.h"

char *my_revstr(char *str)
{
    char c = '\0';
    int len = 0;

    if (str == NULL) {
        return (NULL);
    }
    len = my_strlen(str) - 1;
    for (int i = 0; i <= len / 2; i++) {
        c = str[i];
        str[i] = str[len - i];
        str[len - i] = c;
    }
    return (str);
}
