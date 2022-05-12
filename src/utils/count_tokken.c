/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** count certain tokken
*/

#include <stddef.h>

int check_if_field(int i, char *str, const char *delim, int *is);

int count_tokken(char *str, const char *delim)
{
    int len = 0;
    int is_in_quote = 0;

    if (str == NULL || delim == NULL) {
        return (0);
    }
    for (int i = 0; str[i] != '\0'; i++) {
        if (check_if_field(i, str, delim, &is_in_quote)) {
            len++;
        }
    }
    return (len);
}
