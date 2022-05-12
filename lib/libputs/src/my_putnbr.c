/*
** EPITECH PROJECT, 2021
** LIBMY
** File description:
** put a decimal nbr in stdout
*/

#include "my_puts.h"

static const char base_ten[] = "0123456789";

int my_putnbr(int nb)
{
    int nb_write = 0;

    nb_write = my_putnbr_base(nb, base_ten);
    return (nb_write);
}
