/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** test env related stuff
*/

#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include "my_dico.h"
#include "mysh.h"

// Test(parse_env, null)
// {
//     char **env = NULL;
//
//     cr_assert_null(parse_env(env));
// }
//
// Test(parse_env, bad_value)
// {
//     char *env[] = {
//         "ENV",
//         NULL
//     };
//
//     cr_assert_null(parse_env(env));
// }

Test(parse_env, empty_value)
{
    char *env[] = {
        "ENV=",
        NULL
    };
    dico_t *dict = NULL;

    dict = parse_env(env);
    cr_assert_not_null(dict);
    cr_assert_str_eq(dict->key, "ENV");
    cr_assert_str_eq(dict->value, "");
}

Test(parse_env, one_value)
{
    char *env[] = {
        "SHELL=1",
        NULL
    };
    dico_t *dict = NULL;

    dict = parse_env(env);
    cr_assert_not_null(dict);
    cr_assert_str_eq(dict->key, "SHELL");
    cr_assert_str_eq(dict->value, "1");
    dico_t_destroy(dict);
}

Test(parse_env, two_values)
{
    char *env[] = {
        "SHELL=1",
        "ABC=2",
        NULL
    };
    dico_t *dict = NULL;

    dict = parse_env(env);
    cr_assert_not_null(dict);
    cr_assert_str_eq(dict->key, "SHELL");
    cr_assert_str_eq(dict->value, "1");
    cr_assert_str_eq(dict->next->key, "ABC");
    cr_assert_str_eq(dict->next->value, "2");
    dico_t_destroy(dict);
}
