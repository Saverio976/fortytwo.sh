/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** add only if quote ok
*/

#include <stdlib.h>
#include <unistd.h>
#include "my_clear_str.h"
#include "my_list.h"
#include "my_puts.h"
#include "mysh.h"
#include "my_strings.h"

int count_tokken(char *str, const char *delim);

static list_t *free_all(list_t *list, char const *erros)
{
    write(2, "Unmatched '", 11);
    write(2, erros, my_strlen(erros));
    write(2, "'.\n", 3);
    list_t_destroy(list);
    return (NULL);
}

static char *compute_str_to_add(char *str)
{
    char *new = NULL;

    if (str == NULL) {
        return (NULL);
    }
    new = clear_str(str);
    if (new == NULL) {
        return (str);
    }
    if (new[0] == '\0') {
        free(new);
        free(str);
        return (NULL);
    }
    free(str);
    return (new);
}

list_t *split_str_add_to_list(list_t *list, char *to_add, int *is_first)
{
    if (list == NULL && *is_first != 0) {
        return (NULL);
    }
    if (to_add != NULL) {
        if (count_tokken(to_add, "'") % 2 != 0) {
            return (free_all(list, "'"));
        }
        if (count_tokken(to_add, "\"") % 2 != 0) {
            return (free_all(list, "\""));
        }
    }
    to_add = compute_str_to_add(to_add);
    *is_first += 1;
    return (list_t_add(list, 0, to_add, &free));
}
