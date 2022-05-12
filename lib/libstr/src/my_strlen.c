/*
** EPITECH PROJECT, 2021
** LIBMY
** File description:
** get length of null terminated str
*/

#include <stddef.h>

int my_strlen(char const *str)
{
    int i = 0;

    if (str == NULL) {
        return (-1);
    }
    while (str[i] != '\0') {
        i++;
    }
    return (i);
}
