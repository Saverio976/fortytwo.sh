/*
** EPITECH PROJECT, 2021
** LIBMY
** File description:
** put str to stdout
*/

#include <unistd.h>
#include "my_strings.h"

int my_putstr(char const *str)
{
    int size = 0;
    int nb_write = 0;

    if (str == NULL) {
        return (0);
    }
    size = my_strlen(str);
    if (size == -1) {
        return (0);
    }
    nb_write = write(1, str, size);
    return (nb_write);
}
