/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** check if string is a builtin
*/

#include <stdbool.h>
#include <stddef.h>
#include "builtins.h"
#include "my_strings.h"

const struct builtins_info_s builtins_arr[NB_BUILTINS_FUNC] = {
    {"cd", cd_builtins},
    {"env", env_builtins},
    {"exit", exit_builtins},
    {"setenv", setenv_builtins},
    {"unsetenv", unsetenv_builtins},
    {"alias", alias_builtins}
};

bool check_if_builtins(const char *string)
{
    if (string == NULL) {
        return (false);
    }
    for (int i = 0; i < NB_BUILTINS_FUNC; i++) {
        if (my_strcmp(string, builtins_arr[i].name) == 0) {
            return (true);
        }
    }
    return (false);
}
