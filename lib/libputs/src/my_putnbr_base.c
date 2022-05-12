/*
** EPITECH PROJECT, 2021
** LIBMY
** File description:
** put decimal number in base b
*/

#include <stdlib.h>
#include "my_conversions.h"
#include "my_puts.h"

int my_putnbr_base(int nb, char const *base)
{
    int i = 0;
    char *result = NULL;

    if (base == NULL) {
        return (0);
    }
    result = my_igetstr_base(nb, base);
    i = my_putstr(result);
    free(result);
    return (i);
}
