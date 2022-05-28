/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** find history that start with the start of input
*/

#include <stdbool.h>
#include <stddef.h>
#include "loop.h"
#include "my_dico.h"
#include "my_strings.h"
#include "history.h"

int find_history_backward(dico_t *env, char *input, int start)
{
    bool is_found = false;
    char *tmp = NULL;

    if (env == NULL || input == NULL || start < 0) {
        return (-1);
    }
    while (is_found == false && start >= 0) {
        tmp = get_history_line(env, start);
        if (my_strstartswith(tmp, input)) {
            is_found = true;
            free_secure(tmp);
            break;
        }
        free_secure(tmp);
        start -= 1;
    }
    return ((is_found == true) ? start : -1);
}

int find_history_forward(dico_t *env, char *input, int start)
{
    bool is_found = false;
    char *tmp = NULL;
    int max_hist = inc_history_size(env, 0);

    if (env == NULL || input == NULL || start < 0) {
        return (-1);
    }
    while (is_found == false && start < max_hist) {
        tmp = get_history_line(env, start);
        if (my_strstartswith(tmp, input)) {
            is_found = true;
            free_secure(tmp);
            break;
        }
        free_secure(tmp);
        start += 1;
    }
    return ((is_found == true) ? start : -1);
}
