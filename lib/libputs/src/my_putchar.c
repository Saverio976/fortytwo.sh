/*
** EPITECH PROJECT, 2021
** LIBMY
** File description:
** put char to stdout
*/

#include <unistd.h>

int my_putchar(char c)
{
    int nb_write = 0;

    nb_write = write(1, &c, 1);
    return (nb_write);
}
