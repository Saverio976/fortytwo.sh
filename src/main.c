/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** the main entry point for the project
*/

#include <stddef.h>
#include "my_dico.h"
#include "my_strings.h"
#include "mysh.h"

int main(int ac, char *const av[], char *const env[])
{
    dico_t *dict = NULL;
    int status_code = 0;

    if (ac == 2 && my_strcmp(av[1], "-h") == 0) {
        return (print_help(av[0]));
    }
    dict = parse_env(env);
    if (dict == NULL) {
        return (84);
    }
    status_code = entry_point(dict);
    return (status_code);
}
