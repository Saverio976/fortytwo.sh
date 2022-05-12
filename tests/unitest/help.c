/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** test help function
*/

#include <criterion/criterion.h>
#include "mysh.h"

Test(print_help, basic)
{
    cr_assert_eq(print_help("salut"), 0);
}

Test(print_help, exe_is_null)
{
    cr_assert_eq(print_help(NULL), 0);
}
