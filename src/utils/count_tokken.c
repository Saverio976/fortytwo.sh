/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** count certain tokken
*/

#include <stddef.h>

int check_if_delim(int i, char *str, const char *delim);

int count_tokken(char *str, const char *delim)
{
    int len = 0;

    if (str == NULL || delim == NULL) {
        return (0);
    }
    for (int i = 0; str[i] != '\0'; i++) {
        if (check_if_delim(i, str, delim)) {
            len++;
        }
    }
    return (len);
}
