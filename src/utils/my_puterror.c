/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** put nice error
*/

#include "my_strings.h"
#include <unistd.h>

int my_puterror(const char *exe, const char *str)
{
    int len = 0;

    if (exe == NULL || str == NULL) {
        return (0);
    }
    len += write(2, exe, my_strlen(exe));
    len += write(2, ": ", 2);
    len += write(2, str, my_strlen(str));
    return (len);
}
