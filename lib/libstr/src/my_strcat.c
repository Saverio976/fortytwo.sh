/*
** EPITECH PROJECT, 2021
** LIBMY
** File description:
** concat two string
*/

#include <stddef.h>

char *my_strcat(char *dest, char const *src)
{
    int i = 0;
    int j = 0;

    if (dest == NULL) {
        return (NULL);
    }
    while (dest[i] != '\0') {
        i++;
    }
    for (; src != NULL && src[j] != '\0'; j++) {
        dest[i + j] = src[j];
    }
    dest[i + j] = '\0';
    return (dest);
}
