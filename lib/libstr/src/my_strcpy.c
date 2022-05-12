/*
** EPITECH PROJECT, 2021
** LIBMY
** File description:
** copy a string to another
*/

#include <stddef.h>

char *my_strcpy(char *dest, char const *src)
{
    int i = 0;

    if (src == NULL) {
        return (NULL);
    }
    for (; src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return (dest);
}

char *my_strncpy(char *dest, char const *src, int n)
{
    if (src == NULL) {
        return (NULL);
    }
    for (int i = 0; src[i] != '\0' && i < n; i++) {
        dest[i] = src[i];
    }
    return (dest);
}
