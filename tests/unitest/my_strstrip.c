/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** test my_strstrips
*/

#include <criterion/criterion.h>
#include "my_strings.h"

Test(strips, no_need)
{
    char str[] = "abc";
    char *new = my_strstrip(str, " \t");

    cr_assert_str_eq(str, new);
    free(new);
}

Test(strips, left_only_one_only)
{
    char str[] = "abc";
    char *new = my_strstrip(str, "a");

    cr_assert_str_eq(str + 1, new);
    free(new);
}

Test(strips, right_only_one_only)
{
    char str[] = "abc";
    char *new = my_strstrip(str, "c");

    str[2] = '\0';
    cr_assert_str_eq(str, new);
    free(new);
}

Test(strips, left_only_some)
{
    char str[] = "abc";
    char *new = my_strstrip(str, "ab");

    cr_assert_str_eq(str + 2, new);
    free(new);
}

Test(strips, right_only_some)
{
    char str[] = "abc";
    char *new = my_strstrip(str, "cb");

    str[1] = '\0';
    cr_assert_str_eq(str, new);
    free(new);
}
