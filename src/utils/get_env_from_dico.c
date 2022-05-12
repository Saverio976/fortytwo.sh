/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** get env from dico
*/

#include <stdlib.h>
#include "my_fs.h"
#include "my_dico.h"

static int get_len_dico(dico_t *dico)
{
    int len = 0;
    dico_t *tmp = NULL;

    if (dico == NULL) {
        return (-1);
    }
    tmp = dico;
    do {
        len++;
        tmp = tmp->next;
    } while (tmp != dico);
    return (len);
}

char **get_env_from_dico(dico_t *dico)
{
    int len = 0;
    char **arr = NULL;

    len = get_len_dico(dico);
    if (len < 0) {
        return (NULL);
    }
    arr = malloc(sizeof(char *) * (len + 1));
    if (arr == NULL) {
        return (NULL);
    }
    arr[len] = NULL;
    for (int i = 0; i < len; i++, dico = dico->next) {
        arr[i] = join_path('=', 2, dico->key, dico->value);
    }
    return (arr);
}
