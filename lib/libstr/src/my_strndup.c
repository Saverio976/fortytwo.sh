/*
** EPITECH PROJECT, 2022
** fortytwo.sh
** File description:
** my_strndup
*/

#include <stddef.h>
#include <stdlib.h>

char *my_strndup(char const *str, int n)
{
    int i = 0;
    char *str2 = NULL;

    str2 = malloc(sizeof(char) * n + 1);
    for (i = 0; str[i] != '\0' && i < n; i += 1) {
        str2[i] = str[i];
    }
    str2[i] = '\0';
    return(str2);
}